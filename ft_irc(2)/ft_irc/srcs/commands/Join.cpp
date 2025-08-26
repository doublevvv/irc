#include "../../include/Join.hpp"

Join::Join()
{
	;
}

Join::Join(Join const &obj) : ACommand()
{
	(void)obj;
}

Join& Join::operator=(Join const &obj)
{
	(void)obj;
	return (*this);
}

Join::~Join()
{
	;
}

std::vector<std::string> Join::splitAndTrim(std::string const &str)
{
	std::vector<std::string> result;
	size_t start = 0;

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

		size_t first = 0;
		while (first < token.size() && token[first] == ' ')
		{
			first++;
		}
		size_t last = token.size();
		while (last > first && token[last - 1] == ' ')
		{
			last--;
		}
		token = token.substr(first, last - first);
		std::cout << "first: " << first << std::endl;
		std::cout << "last: " << last << std::endl;
		std::cout << "TOKEN: " << token << std::endl;

		if (!token.empty())
		{
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

void Join::leaveAllChannels(Server &server, Client* client)
{
	std::map<std::string, Channel*> &channels = server.getChannels();
	std::map<std::string, Channel*>::iterator it = channels.begin();

	while (it != channels.end())
	{
		Channel *chan = it->second;
		if (chan->isClientInChannel(client->getNick()))
		{
			chan->removeClientFromChannel(client->getNick());
		}
		it++;
	}
}

void Join::execute(Server &server, std::string const &command, std::vector<Client*>::iterator it, std::string const &args)
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
		return ;
	}
	if (channelsStr.empty())
	{
		output.insert(std::pair<std::string, std::set<int> >(ERR_NEEDMOREPARAMS((*it)->getNick()), fds));
		return;
	}
	if (channelsStr == "0")
	{
		leaveAllChannels(server, *it);
		output.insert(std::pair<std::string, std::set<int> >((*it)->getNick() + " has been removed from " + channelsStr + "\n", fds));
		return;
	}

	std::string channelsKeys;
	std::getline(ss, channelsKeys);

	std::vector<std::string> channels = splitAndTrim(channelsStr);
	std::vector<std::string> keys = splitAndTrim(channelsKeys);

	for (size_t i = 0; i < channels.size(); ++i)
	{
		std::string &channelName = channels[i];

		// Verification du prefixe du salon
		if (channelName[0] != '#' && channelName[0] != '&')
		{
			std::cerr << "Error: Channel name must start with # or &" << std::endl;
			output.insert(std::pair<std::string, std::set<int> >(ERR_BADCHANMASK((*it)->getNick(), channelName), fds));
			return ;
			// continue; // passer au channel suivant
		}

		std::string key = "";
		if (i < keys.size())
		{
			key = keys[i];
			std::cout << "Channel: " << channels[i] << " | Key: ";
			if (key.empty())
			{
				std::cout << "(none)";
			}
			else
			{
				std::cout << key;
			}
			std::cout << std::endl;
			i++;
		}

		//joinChannel(server, *it, channels[i], key);
		std::map<std::string, Channel*> &serverChannels = server.getChannels();
		Channel *chan = NULL;
		std::map<std::string, Channel*>::iterator ite = serverChannels.find(channelName);

		if (ite != serverChannels.end())
		{
			chan = ite->second;

			if (!chan->getPassword().empty() && chan->getPassword() != key)
			{
				std::cout << "chan password: " << chan->getPassword() << std::endl;
				std::cout << "key: " << key << std::endl;
				output.insert(std::pair<std::string, std::set<int> >(ERR_BADCHANNELKEY((*it)->getUser(), channelName), fds));
				return;
			}

			if (chan->isInviteOnly() && !chan->isInvited((*it)->getNick()))
			{
				output.insert(std::pair<std::string, std::set<int> >(ERR_INVITEONLYCHAN((*it)->getNick(), channelName), fds));
				return;
			}

			if (chan->getLimit() != -1 && chan->getNbUsers() >= chan->getLimit())
			{
				output.insert(std::pair<std::string, std::set<int> >(ERR_CHANNELISFULL((*it)->getNick(), channelName), fds));
				return;
			}

			if (!chan->isClientInChannel((*it)->getNick()))
			{
				chan->addClientToChannel(*it);
				(*it)->setStatus(MEMBER);
			}
		}
		else
		{
			// Créer le channel si inexistant
			chan = new Channel(channelName);
			chan->setName(channelName);
			chan->setPassword(key);
			(*it)->setStatus(OPERATOR);
			chan->addClientToChannel((*it));
			server.addChannelToChannels(*chan);
		}
		output.insert(std::pair<std::string, std::set<int> >("Client " + (*it)->getNick() + " joined channel " + chan->getName() + "\n", fds));
		chan->displayMap();
	}
}
