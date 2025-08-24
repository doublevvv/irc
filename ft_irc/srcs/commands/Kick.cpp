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

void Kick::execute(Server &server, std::string const &command, std::vector<Client*>::iterator it, std::string const &args)
{
	std::cout << "Entering " << command << " command" << std::endl;
	std::stringstream ss(args);
	std::string word;
	int count = 0;

	while (ss >> word)
	{
		count++;
	}
	if (count < 2 || count > 3)
	{
		server.sendMsgtoClient((*it)->getFd(), ERR_NEEDMOREPARAMS((*it)->getNick()));
		return ;
	}

	ss.clear();
	ss.seekg(0);
	std::string channelName;
	std::string user;
	std::string comment;
	ss >> channelName >> user >> comment;

	std::cout << "channelName: " << channelName << std::endl;
	std::cout << "user: " << user << std::endl;
	std::cout << "comment: " << comment << std::endl;

	if (!((*it))->tryJoinChannel())
	{
		return ;
	}
	// Verification si channel existe
	std::map<std::string, Channel*> &channels = server.getChannels();
	std::map<std::string, Channel*>::iterator ite = channels.find(channelName);
	if (ite == channels.end())
	{
		server.sendMsgtoClient((*it)->getFd(), ERR_NOSUCHCHANNEL((*it)->getNick(), channelName));
		return;
	}
	// Verification si user a kick est dans le channel
	if (!ite->second->isClientInChannel((*it)->getNick()))
	{
		std::cerr << "Error: user " << user << " not in channel" << std::endl;
		server.sendMsgtoClient((*it)->getFd(), ERR_USERNOTINCHANNEL((*it)->getNick(), channelName));
		return ;
	}
	// Verification l’emetteur est operateur du channel
	if ((*it)->getStatus() != OPERATOR)
	{
		server.sendMsgtoClient((*it)->getFd(), ERR_CHANOPRIVISNEEDED((*it)->getNick(), channelName));
		return;
	}
	std::cout << "first: " << ite->first << std::endl;
	std::cout << "second: " << ite->second << std::endl;
	server.removeClient((*it)->getNick());
	if (comment.empty())
	{
		std::cout << (*it)->getNick() << " has been kicked from " << channelName << std::endl;
	}
	else
	{
		std::cout << (*it)->getNick() << " has been kicked from " << channelName << " because " << comment << std::endl;
	}
}

