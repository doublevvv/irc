#include "../../include/Pass.hpp"

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

void Pass::execute(std::string const &command, Client &client, const std::string &args)
{
	(void)client;
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
		std::cout << ERR_NEEDMOREPARAMS(client.getNick());
		return ;
	}

	ss.clear();
	ss.seekg(0);
	std::string password;
	ss >> password;
	if (client.getUse() == true)
	{
		std::cout << ERR_ALREADYREGISTERED(client.getNick());
		return ;
	}
	else
		client.setPass(password);

	std::cout << "PASSWORD: " << client.getPass() << std::endl;
}
