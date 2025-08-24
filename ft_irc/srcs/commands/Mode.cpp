#include "../../include/Mode.hpp"

Mode::Mode()
{
	;
}

Mode::Mode(Mode const &obj) : ACommand()
{
	(void)obj;
}

Mode& Mode::operator=(Mode const &obj)
{
	(void)obj;
	return (*this);
}

Mode::~Mode()
{
	;
}

void Mode::execute(Server &server, std::string const &command, std::vector<Client*>::iterator it, std::string const &args)
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
	if (count < 2)
	{
		server.sendMsgtoClient((*it)->getFd(), ERR_NEEDMOREPARAMS((*it)->getNick()));
		return ;
	}

	ss.clear();
	ss.seekg(0);

	std::string channelName;
	std::string modeFlag;
	ss >> channelName >> modeFlag;
	std::cout << "channelName: " << channelName << std::endl;
	std::cout << "modeFlag: " << modeFlag << std::endl;

	if (!((*it))->tryJoinChannel())
	{
		return ;
	}
	// Verifier si le channel existe
	std::map<std::string, Channel*> &channels = server.getChannels();
	std::map<std::string, Channel*>::iterator ite = channels.find(channelName);

	if (ite == channels.end())
	{
		server.sendMsgtoClient((*it)->getFd(), ERR_NOSUCHCHANNEL((*it)->getNick(), channelName));
		return;
	}

	if (modeFlag == "+i" || modeFlag == "-i") // Set/remove Invite-only channel
	{
		if (ite->second->modeI((*it)->getNick(), modeFlag))
		{
			std::cout << "Invite mode set to " << ite->second->getInvited() << std::endl;
		}
		else
		{
			std::cerr << "Error: " << (*it)->getNick() << " cannot change invite mode" << std::endl;
		}
	}
	else if (modeFlag == "+k" || modeFlag == "-k") // Set/remove the channel key (password)
	{
		std::string password;
		ss >> password;
		if (ite->second->modeK((*it)->getNick(), modeFlag, password))
		{
			std::cout << "new password: " << password /*  */<< std::endl;
			std::cout << "Channel key has been changed" << std::endl;
		}
		else
		{
			std::cerr << "Error: " << (*it)->getNick() << " cannot change channel key" << std::endl;
		}
	}
	else if (modeFlag == "+l" || modeFlag == "-l") // Set/remove the user limit to channel
	{
		std::string userLimit;
		ss >> userLimit;
		std::cout << "userLimit: " << userLimit << std::endl;
		int limit = atoi(userLimit.c_str());
		std::cout << "limit: " << limit << std::endl;
		if (ite->second->modeL((*it)->getNick(), modeFlag, limit))
		{
			std::cout << "User " << (*it)->getNick() << " limited the channel to " << ite->second->getLimit() << " user(s)" << std::endl;
		}
		else
		{
			std::cerr << "Error: " << (*it)->getNick() << " cannot change user limit" << std::endl;
		}
	}
	else if (modeFlag == "+o" || modeFlag == "-o") // Give/take channel operator privilege
	{
		std::string target;
		target = args.substr(modeFlag.length(), args.length());
		if (ite->second->modeO((*it)->getNick(), modeFlag, target))
		{
			std::cout << "User " << (*it)->getNick() << "granted " << target << " the operator role " << std::endl;
		}
		else
		{
			std::cerr << "Error: " << (*it)->getNick() << " cannot change channel operator privilege" << std::endl;
		}
	}
	else if (modeFlag == "+t" || modeFlag == "-t") // Set/remove the restrictions of the TOPIC command to channel operators
	{
		if (ite->second->modeT((*it)->getNick(), modeFlag))
		{
			std::cout << "User " << (*it)->getNick() << " changed topic restrictions to " << ite->second->getTopicRestrictions() << std::endl;
		}
		else
		{
			std::cerr << "Error: " << (*it)->getNick() << " cannot change topic restriction" << std::endl;
		}
	}
	else
	{
		std::cerr << "Unknown mode: " << modeFlag << std::endl;
	}
}
