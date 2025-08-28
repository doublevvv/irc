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
	// std::vector<std::string> &invitedChannels = getInvitedChannels();
	// std::vector<std::string>::iterator chanIt = find(invitedChannels.begin(), invitedChannels.end(), client->getNick());

	// invitedChannels->removeClientFromInvited(client->getNick());
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
		output.insert(std::pair<std::string, std::set<int> >("Client must register to access to channels\r\n", fds));
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
		output.insert(std::pair<std::string, std::set<int> >((*it)->getNick() + " has quit channels" + "\n", fds));
		return;
	}

	std::string channelsKeys;
	//std::getline(ss, channelsKeys);
	ss >> channelsKeys;
	std::cout << "channelsKey: " << channelsKeys << std::endl;

	std::vector<std::string> channels = splitAndTrim(channelsStr);
	std::vector<std::string> keys = splitAndTrim(channelsKeys);

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

		std::string key = "";
		if (i < keys.size())
		{
			key = keys[i];
			std::cout << "key: " << key << std::endl;
		}

		std::map<std::string, Channel*> &serverChannels = server.getChannels();
		Channel *chan = NULL;
		std::map<std::string, Channel*>::iterator ite = serverChannels.find(channelName);

		if (ite != serverChannels.end())
		{
			chan = ite->second;
			if (!chan->getPassword().empty() && chan->getPassword() != key)
			{
				std::string pass = chan->getPassword();
				std::cout << "chan password: " << chan->getPassword() << std::endl;
				std::cout << "key: " << key << std::endl;
				std::cout << "chan password length: " << chan->getPassword().size() << std::endl;
				std::cout << "key length: " << key.size() << std::endl;
				// for (size_t i = 0; i < pass.length(); i++)
				// {
				// 	std::cout << "pass[i] = " << (int)pass[i] << std::endl;
				// }
				// std::cout << "----------------------------------------" << std::endl;

				// for (size_t i = 0; i < key.length(); i++)
				// {
				// 	std::cout << "key[i] = " << (int)key[i] << std::endl;
				// }
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
				(*it)->setStatus(MEMBER);
				chan->addClientToChannel(*it);
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
		std::set<int> set = chan->noMsgforme((*it));
		std::cout << "NICK JOIN = " << (*it)->getNick() << std::endl;
		std::cout << "USER JOIN = " << (*it)->getUser() << std::endl;
		std::cout << "CHANNAME JOIN = " << chan->getName() << std::endl;


		std::string joinMsg = ":" + (*it)->getNick() + "!~" + (*it)->getUser() + "@host JOIN :" + chan->getName() + "\r\n";
		std::string topicMsg = "332 " + (*it)->getNick() + " " + chan->getName() + " :" + chan->getTopic() + "\r\n";
		std::string namesMsg = "353 " + (*it)->getNick() + " = " + chan->getName() + " :" + chan->getClientList(). + "\r\n";
		std::string endOfNamesMsg = "366 " + (*it)->getNick() + " " + chan->getName() + " :End of /NAMES list\r\n";

		output[joinMsg].insert(set.begin(), set.end());
		output[topicMsg].insert(fds.begin(), fds.end());
		output[namesMsg].insert(fds.begin(), fds.end());
		output[endOfNamesMsg].insert(fds.begin(), fds.end());

		// output.insert(std::pair<std::string, std::set<int> >(RPL_JOIN((*it)->getNick(), (*it)->getUser(), "JOIN", chan->getName()), fds));
		// output[RPL_JOIN((*it)->getNick(), (*it)->getUser(), "JOIN", chan->getName())].insert(set.begin(), set.end());
		// if (!chan->getTopic().empty())
		// 	output[RPL_TOPIC((*it)->getNick(), chan->getName(), chan->getTopic())].insert(set.begin(), set.end());
		// 	// output.insert(std::pair<std::string, std::set<int> >(RPL_TOPIC((*it)->getNick(), chan->getName(), chan->getTopic()), fds));
		// // output.insert(std::pair<std::string, std::set<int> >(RPL_NAMREPLY((*it)->getNick(), chan->getName(), "hello"), fds));
		// output[RPL_NAMREPLY((*it)->getNick(), chan->getName(), "hello")].insert(set.begin(), set.end());
		// // output.insert(std::pair<std::string, std::set<int> >(RPL_ENDOFNAME((*it)->getNick(),chan->getName()), fds));
		// output[RPL_ENDOFNAME((*it)->getNick(),chan->getName())].insert(set.begin(), set.end());
		// output[RPL_JOIN((*it)->getNick(), (*it)->getUser(), "JOIN", chan->getName())].insert(set.begin(), set.end());
		// std::map<std::string, Client *> &listclient = chan->getClientList();
		// Le message affiche seulement le nom du dernier channel;
		/* **** DEBUG **** */
		chan->displayMap();
		/* **************** */
	}
}

