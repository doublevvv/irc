#include "../../include/Part.hpp"

Part::Part()
{
	;
}

Part::Part(Part const &obj) : ACommand()
{
	(void)obj;
}

Part& Part::operator=(Part const &obj)
{
	(void)obj;
	return (*this);
}

Part::~Part()
{
	;
}

std::vector<std::string> Part::splitAndTrim(std::string const &str)
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

void Part::execute(Server &server, std::string const &command, std::vector<Client*>::iterator it, std::string const &args)
{
	std::cout << "Entering " << command << " command" << std::endl;

	std::stringstream ss(args);
	std::string channelsStr;
	ss >> channelsStr;
	std::set<int> fds;
	fds.insert((*it)->getFd());
	std::map<std::string, std::set<int> > &output = server.getOutput();

	if (channelsStr.empty())
	{
		output.insert(std::pair<std::string, std::set<int> >(ERR_NEEDMOREPARAMS((*it)->getNick()), fds));
		return;
	}

	// Recuperer le message optionnel (commentaire)
	std::string comment;
	// std::getline(ss, comment);
	ss >> comment;
	std::cout << "comment: " << comment << std::endl;

	std::vector<std::string> channels = splitAndTrim(channelsStr);

	// size_t start = 0;
	// while (true)
	// {
	// 	size_t pos = channelsStr.find(',', start);
	// 	std::string token;
	// 	if (pos == std::string::npos)
	// 	{
	// 		token = channelsStr.substr(start);
	// 	}
	// 	else
	// 	{
	// 		token = channelsStr.substr(start, pos - start);
	// 	}
	// 	size_t first = 0;
	// 	while (first < token.size() && token[first] == ' ')
	// 	{
	// 		first++;
	// 	}
	// 	size_t last = token.size();
	// 	while (last > first && token[last - 1] == ' ')
	// 	{
	// 		last--;
	// 	}
	// 	token = token.substr(first, last - first);
	// 	if (!token.empty())
	// 	{
	// 		channels.push_back(token);
	// 	}
	// 	if (pos == std::string::npos)
	// 	{
	// 		break;
	// 	}
	// 	start = pos + 1;
	// }

	// Boucle sur chaque channel
	for (size_t i = 0; i < channels.size(); ++i)
	{
		std::string &channelName = channels[i];

		// Verifier que le channel commence par # ou &
		if ((channelName[0] != '#' && channelName[0] != '&'))
		{
			output.insert(std::pair<std::string, std::set<int> >(ERR_BADCHANMASK((*it)->getNick(), channelName), fds));
			return ;
		}

		// Verifier que le channel existe
		std::map<std::string, Channel*> &serverChannels = server.getChannels();
		std::map<std::string, Channel*>::iterator ite = serverChannels.find(channelName);
		if (ite == serverChannels.end())
		{
			output.insert(std::pair<std::string, std::set<int> >(ERR_NOSUCHCHANNEL((*it)->getNick(), channelName), fds));
			return ;
		}

		Channel *chan = ite->second;

		// Verifier que le client est dans le channel
		if (!chan->isClientInChannel((*it)->getNick()))
		{
			output.insert(std::pair<std::string, std::set<int> >(ERR_NOTONCHANNEL((*it)->getNick(), channelName), fds));
			return ;
		}

		// Supprimer le client du channel
		chan->removeClientFromChannel((*it)->getNick());
		std::cout << (*it)->getNick() << " left " << channelName;
		if (!comment.empty())
		{
			std::cout << " (" << comment << ")" << std::endl;
		}

		// Envoyer message PART au client
		output.insert(std::pair<std::string, std::set<int> >(RPL_PART((*it)->getNick(), (*it)->getReal(), command, channelName, comment), fds));
	}
}
