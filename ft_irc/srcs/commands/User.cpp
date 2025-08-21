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

void User::execute(std::string const &command, Client &client, const std::string &args)
{
	std::cout << "Entering " << command << " command" << std::endl;
	std::stringstream ss(args);
	std::string word;
	int count = 0;

	while (ss >> word)
	{
		count++;
	}
	std::cout << " FD = " << client.getFd() << std::endl;
	if (count != 4)
	{
		client.sendMsgtoClient(client.getFd(), ERR_NEEDMOREPARAMS(client.getNick()));
		// std::cout << ERR_NEEDMOREPARAMS(client.getNick());
		return ;
	}

	// reflechir a la taille du username ?
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
		std::cerr << command << ": arg mode must be zero\n";
		return ;
	}
	if (unused != '*')
	{
		std::cout << command << ": unused must be 'asterisk'" << std::endl;
		return ;
	}
	if (client.getUse())
	{
		std::cout << ERR_ALREADYREGISTERED(username);
		return ;
	}
	else
	{
		client.setUser(username);
		client.setReal(realname);
		client.setUse(true);
	}

	std::cout << "USERNAME: " << client.getUser() << std::endl;
	std::cout << "REALNAME: " << client.getReal() << std::endl;
}
