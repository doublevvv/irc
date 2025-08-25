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
	std::set<int> fds;
	fds.insert((*it)->getFd());
	std::map<std::string, std::set<int> > &output = server.getOutput();

	while (ss >> word)
	{
		count++;
	}
	std::cout << "count = " << count << std::endl;
	if (count < 2)
	{
		output.insert(std::pair<std::string, std::set<int> >(ERR_NEEDMOREPARAMS((*it)->getNick()), fds));
		return ;
	}

	ss.clear();
	ss.seekg(0); //ss.str(args);

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
		output.insert(std::pair<std::string, std::set<int> >(ERR_NOSUCHCHANNEL((*it)->getNick(), channelName), fds));
		return;
	}

	// Verifier que l’emetteur est operateur du channel
	if (!ite->second->isOperator((*it)->getNick()))
	{
		output.insert(std::pair<std::string, std::set<int> >(ERR_CHANOPRIVISNEEDED((*it)->getNick(), channelName), fds));
		return;
	}
	if (modeFlag == "+i" || modeFlag == "-i") // Set/remove Invite-only channel
	{
		if (ite->second->modeI((*it)->getNick(), modeFlag))
		{
			std::cout << "Invite mode set to" <<  ite->second->isInviteOnly() << std::endl;
			//output.insert(std::pair<std::string, std::set<int> >("Invite mode set to " + ite->second->isInviteOnly(), fds));
		}
		else
		{
			output.insert(std::pair<std::string, std::set<int> >(ERR_NOSUCHCHANNEL((*it)->getNick(), channelName), fds));
		}
	}
	else if (modeFlag == "+k" || modeFlag == "-k") // Set/remove the channel key (password)
	{
		std::string password;
		ss >> password;
		if (ite->second->modeK((*it)->getNick(), modeFlag, password))
		{
			std::cout << "new password: " << password << std::endl;
			output.insert(std::pair<std::string, std::set<int> >( "Channel key has been changed\n", fds));
		}
		else
		{
			output.insert(std::pair<std::string, std::set<int> >((*it)->getNick() + " cannot change channel key\n", fds));
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
			std::cout << "User " << (*it)->getNick() << " limited the channel to " << ite->second->getLimit() << " user(s)\n" << std::endl;
			//output.insert(std::pair<std::string, std::set<int> >((*it)->getNick() + " limited the channel to " + (ite->second->getLimit()) + " user(s)\n", fds));
		}
		else
		{
			output.insert(std::pair<std::string, std::set<int> >((*it)->getNick() + " cannot change user limit", fds));
		}
	}
	else if (modeFlag == "+o" || modeFlag == "-o") // Give/take channel operator privilege
	{
		std::string target;
		ss >> target;
		std::cout << "target: " << target << std::endl;
		if (ite->second->modeO((*it)->getNick(), modeFlag, target))
		{
			output.insert(std::pair<std::string, std::set<int> >((*it)->getNick() + " granted " + target + "the operator role\n", fds));
		}
		else
		{
			output.insert(std::pair<std::string, std::set<int> >((*it)->getNick() + " cannot change channel operator privilege\n", fds));
		}
	}
	else if (modeFlag == "+t" || modeFlag == "-t") // Set/remove the restrictions of the TOPIC command to channel operators
	{
		if (ite->second->modeT((*it)->getNick(), modeFlag))
		{
			std::cout << "User " << (*it)->getNick() << " changed topic restrictions to " << ite->second->isTopicRestricted() << std::endl;
		}
		else
		{
			output.insert(std::pair<std::string, std::set<int> >((*it)->getNick() + " cannot change topic restriction\n", fds));
		}
	}
	else
	{
		std::cerr << "Unknown mode: " << modeFlag << std::endl;
	}
}
