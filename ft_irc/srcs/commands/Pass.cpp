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
	std::set<int> fds;
	fds.insert((*it)->getFd());
	std::map<std::string, std::set<int> > &output = server.getOutput();

	while (ss >> word)
	{
		count++;
	}
	std::cout << "count = " << count << std::endl;
	if (count != 1)
	{
		output.insert(std::pair<std::string, std::set<int> >(ERR_NEEDMOREPARAMS((*it)->getNick()), fds));
		return ;
	}

	ss.clear();
	ss.seekg(0);
	std::string password;
	ss >> password;
	if ((*it)->getUse() == true)
	{
		output.insert(std::pair<std::string, std::set<int> >(ERR_ALREADYREGISTERED((*it)->getNick()), fds));
		return ;
	}
	else
		(*it)->setPass(password);

	std::cout << "PASSWORD: " << (*it)->getPass() << std::endl;
}
