#include "../../include/Pass.hpp"
#include "../../include/Server.hpp"

Pass::Pass()
{
	;
}

Pass::Pass(Pass const &obj)
{
	(void)obj;
}

Pass& Pass::operator=(Pass const &obj)
{
	(void)obj;
	return (*this);
}

Pass::~Pass()
{
	;
}

void Pass::execute(Server &server, std::string const &command, std::vector<Client*>::iterator it, const std::string &args)
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
	if (count != 1)
	{
		server.sendMsgtoClient((*it)->getFd(), ERR_NEEDMOREPARAMS((*it)->getNick()));
		// std::cout << ERR_NEEDMOREPARAMS((*it)->getNick());
		return ;
	}

	ss.clear();
	ss.seekg(0);
	std::string password;
	ss >> password;
	if ((*it)->getUse() == true)
	{
		std::cout << ERR_ALREADYREGISTERED((*it)->getNick());
		return ;
	}
	else
		(*it)->setPass(password);

	std::cout << "PASSWORD: " << (*it)->getPass() << std::endl;
}
