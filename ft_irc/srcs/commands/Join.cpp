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

// JOIN autant de channels qu'on souhaite ?
// Gestion des arguments
void Join::execute(Server &server, std::string const &command, std::vector<Client*>::iterator it, std::string const &args)
{
	std::cout << "Entering " << command << " command" << std::endl;

	std::stringstream ss(args);
	std::string word;
	int count = 0;

	while (ss >> word)
	{
		count++;
	}
	std::cout << "count = " << count << std::endl;
	if (count < 1)
	{
		server.sendMsgtoClient((*it)->getFd(), ERR_NEEDMOREPARAMS((*it)->getNick()));
		return ;
	}

	ss.clear();
	ss.seekg(0);
	std::string channelName;
	std::string key;
	ss >> channelName >> key;
	std::cout << "channelName: " << channelName << std::endl;
	std::cout << "key: " << key << std::endl;

	if (!((*it))->tryJoinChannel())
	{
		return ;
	}
	Channel *chan = NULL;
	std::map<std::string, Channel*> &channels = server.getChannels();
	std::map<std::string, Channel*>::iterator ite = channels.find(channelName);

	if (ite != channels.end())
	{
		std::cout << ite->first << " channel already exists" << std::endl;
		// Verification mot de passe du salon
		if (chan->getPassword() != key)
		{
			server.sendMsgtoClient((*it)->getFd(), ERR_BADCHANNELKEY((*it)->getNick(), channelName));
			return ;
		}
		if (!chan->isClientInChannel((*it)->getNick()))
		{
			chan->addClientToChannel((*it));
			(*it)->setStatus(MEMBER);
		}
		// Verification si channel est en mode +i
		if (chan->getInvited() && !chan->isInvited((*it)->getNick()))
		{
			std::cerr << "JOIN failed: you are not invited to " << channelName << std::endl;
			server.sendMsgtoClient((*it)->getFd(), ERR_INVITEONLYCHAN((*it)->getNick(), channelName));
			return;
		}
		// Verification limite d’utilisateurs
		if (chan->getLimit() != -1 && chan->getNbUsers() >= chan->getLimit())
		{
			std::cerr << "JOIN failed: channel " << channelName << " is full" << std::endl;
			server.sendMsgtoClient((*it)->getFd(), ERR_CHANNELISFULL((*it)->getNick(), channelName));
			return;
		}
		else
		{
			std::cout << (*it)->getNick() << " is already in channel " << chan->getName() << std::endl;
		}
	}
	else
	{
		// Créer un nouveau channel
		std::cout << "Create a chan" << std::endl;
		chan = new Channel(channelName);
		chan->setName(channelName);
		chan->setPassword(key);
		std::cout << "channel name: " << chan->getName() << std::endl;
		(*it)->setStatus(OPERATOR);
		std::cout << "fd: " << (*it)->getFd() << std::endl;
		std::cout << "second: " << ite->second << std::endl;
		chan->addClientToChannel((*it));
		server.addChannelToChannels(*chan);
	}

	std::cout << "user is " << (*it)->getStatus() << std::endl;
	std::cout << (*it)->getNick() << " has been added to channel " << chan->getName() << std::endl;
	std::cout << "JOIN success: " << (*it)->getNick() << " joined " << chan->getName() << std::endl;

	chan->displayMap();
}
