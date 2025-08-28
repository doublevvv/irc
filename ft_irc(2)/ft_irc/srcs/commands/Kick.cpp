#include "../../include/Kick.hpp"

Kick::Kick()
{
	;
}

Kick::Kick(Kick const &obj) : ACommand()
{
	(void)obj;
}

Kick& Kick::operator=(Kick const &obj)
{
	(void)obj;
	return (*this);
}

Kick::~Kick()
{
	;
}

std::vector<std::string> Kick::splitAndTrim(std::string const &str)
{
	std::vector<std::string> result;
	size_t start = 0;

	std::cout << "str = " << str << std::endl;
	while (true)
	{
		size_t pos = str.find(',', start);
		std::string token;

		if (pos == std::string::npos)
		{
			token = str.substr(start);
			std::cout << "token if: " << token << std::endl;
		}
		else
		{
			token = str.substr(start, pos - start);
			std::cout << "token else: " << token << std::endl;
		}
		if (!token.empty())
		{
			std::cout << "token avant ajout " << token << std::endl;
			result.push_back(token);
		}
		if (pos == std::string::npos)
		{
			break;
		}
		start = pos + 1;
	}
	return (result);
}

void Kick::execute(Server &server, std::string const &command, std::vector<Client*>::iterator it, std::string const &args)
{
	std::cout << "Entering " << command << " command" << std::endl;
	std::stringstream ss(args);
	std::string channelsStr;
	ss >> channelsStr;
	std::set<int> fds;
	fds.insert((*it)->getFd());
	std::map<std::string, std::set<int> > &output = server.getOutput();

	if (!((*it))->tryJoinChannel())
	{
		output.insert(std::pair<std::string, std::set<int> >("Client must register to access to channels\r\n", fds));
		return ;
	}
	if (channelsStr.empty())
	{
		output.insert(std::pair<std::string, std::set<int> >(ERR_NEEDMOREPARAMS((*it)->getNick()), fds));
		return;
	}

	std::string channelsUsers;
	//std::getline(ss, channelsUsers);
	ss >> channelsUsers;
	std::cout << "channelsUsers: " << channelsUsers << std::endl;

	std::vector<std::string> channels = splitAndTrim(channelsStr);
	std::vector<std::string> users = splitAndTrim(channelsUsers);

	std::string comment;
	ss >> comment;

	for (size_t i = 0; i < channels.size(); i++)
	{
		std::cout << "channels["<<i<<"]: " << channels[i] << std::endl;
		std::string &channelName = channels[i];

		if (channelName[0] != '#' && channelName[0] != '&')
		{
			std::cerr << "Error: Channel name must start with # or &" << std::endl;
			output.insert(std::pair<std::string, std::set<int> >(ERR_BADCHANMASK((*it)->getNick(), channelName), fds));
			return ;
		}
		std::cout << "channelName: " << channelName << std::endl;

		std::string user = "";
		if (i < users.size())
		{
			user = users[i];
			std::cout << "user: " << user << std::endl;
		}

		std::map<std::string, Channel*> &serverChannels = server.getChannels();
		std::map<std::string, Channel*>::iterator ite = serverChannels.find(channelName);


		if (ite == serverChannels.end())
		{
			output.insert(std::pair<std::string, std::set<int> >(ERR_NOSUCHCHANNEL((*it)->getNick(), channelName), fds));
			return;
		}

		// Verifier que le client cible existe dans le serveur
		std::vector<Client*> clients = server.getClients();
		Client *targetClient = NULL;

		for (size_t i = 0; i < clients.size(); ++i)
		{
			if (clients[i]->getNick() == user)
			{
				targetClient = clients[i];
				break;
			}
		}

		if (!targetClient)
		{
			output.insert(std::pair<std::string, std::set<int> >(ERR_USERNOTINCHANNEL(user, channelName), fds));
			return;
		}

		// Verification si user a kick est dans le channel
		std::cout << "USER: " << user << std::endl;
		if (!ite->second->isClientInChannel(user))
		{
			output.insert(std::pair<std::string, std::set<int> >(ERR_USERNOTINCHANNEL(user, channelName), fds));
			return ;
		}
		// Verifier que l’emetteur est operateur du channel
		if (!ite->second->isOperator((*it)->getNick()))
		{
			output.insert(std::pair<std::string, std::set<int> >(ERR_CHANOPRIVISNEEDED((*it)->getNick(), channelName), fds));
			return;
		}
		ite->second->removeClientFromChannel(user);
		// if (!ite->second->isClientInInvited((*it)->getNick()))
		// {
		// 	ite->second->removeClientFromInvited((*it)->getNick());
		// }
		if (comment.empty())
		{
			output.insert(std::pair<std::string, std::set<int> >(user + " has been kicked from " + channelName + "\r\n", fds));
		}
		else
		{
			output.insert(std::pair<std::string, std::set<int> >(user + " has been kicked from " + channelName + " because " + comment +"\r\n", fds));
		}
	}
}
