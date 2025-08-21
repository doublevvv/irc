#include "../../include/User.hpp"

User::User()
{
	;
}

User::User(User const &obj)
{
	(void)obj;
}

User& User::operator=(User const &obj)
{
	(void)obj;
	return (*this);
}

User::~User()
{
	;
}

void User::execute(Server &server, std::string const &command, std::vector<Client*>::iterator it, std::string const &args)
{
	std::cout << "Entering " << command << " command" << std::endl;
	std::stringstream ss(args);
	std::string word;
	int count = 0;

	while (ss >> word)
	{
		count++;
	}
	std::cout << " FD = " << (*it)->getUse() << std::endl;
	if (count != 4)
	{
		server.sendMsgtoClient((*it)->getFd(), ERR_NEEDMOREPARAMS((*it)->getNick()));
		return ;
	}

	ss.clear();
	ss.seekg(0);
	std::string username;
	int mode;
	char unused;
	std::string realname;

	ss >> username >> mode >> unused >> realname;
	std::cout << "username: " << username << std::endl;
	std::cout << "mode: " << "" << mode << std::endl;
	std::cout << "unused: " << unused << std::endl;
	std::cout << "realname:" << realname << std::endl;

	if (mode != 0)
	{
		server.sendMsgtoClient((*it)->getFd(), "USER: arg mode must be zero\n");
		return ;
	}
	if (unused != '*')
	{
		server.sendMsgtoClient((*it)->getFd(), "USER: unused must be 'asterisk'\n");
		return ;
	}
	if ((*it)->getUse())
	{
		server.sendMsgtoClient((*it)->getFd(), ERR_ALREADYREGISTERED((*it)->getUser()));
		return ;
	}
	else
	{
		(*it)->setUser(username);
		(*it)->setReal(realname);
		(*it)->setUse(true);
	}

	std::cout << "USERNAME: " << (*it)->getUser() << std::endl;
	std::cout << "REALNAME: " << (*it)->getReal() << std::endl;
}
