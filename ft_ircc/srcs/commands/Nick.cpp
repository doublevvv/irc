#include "../../include/Nick.hpp"

Nick::Nick()
{
	;
}

Nick::Nick(Nick const &obj) : ACommand()
{
	(void)obj;
}

Nick& Nick::operator=(Nick const &obj)
{
	(void)obj;
	return (*this);
}

Nick::~Nick()
{
	;
}

void Nick::execute(Server &server, std::string const &command, std::vector<Client*>::iterator it, std::string const &args)
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
		std::cout << "word:" << word << std::endl;
		count++;
	}
	std::cout << "count: " << count << std::endl;
	if (count < 1)
	{
		// output.insert(std::pair<std::string, std::set<int> >(ERR_NONICKNAMEGIVEN, fds));
		output[ERR_NONICKNAMEGIVEN].insert((*it)->getFd());
		return ;
	}
	ss.clear();
	ss.seekg(0);
	std::string nickname;
	ss >> nickname;


	if (!((*it))->tryRegister())
	{
		return ;
	}
	if (nickname.size() > 10)
	{
		std::cout << "NICK: max length for nickname is 9\n";
		return ;
		// ! return here, must nt go in the setnick function
	}
	for (unsigned int i = 0; i < nickname.size(); i++)
	{
		if (nickname[i] == ' ' || nickname[i] == ' ' || nickname[i] == ',' || nickname[i] == '*' || nickname[i] == '?' ||
			nickname[i] == '!' || nickname[i] == '@' || nickname[i] == '.' || nickname[i] == '$' || nickname[i] == ':')
		{
			output.insert(std::pair<std::string, std::set<int> >(ERR_ERRONEUSNICKNAME((*it)->getNick(), (*it)->getNick()), fds));
			return ;
		}
	}
	std::vector<Client*> clients = server.getClients();
    for (size_t i = 0; i < clients.size(); ++i)
    {
        if (clients[i]->getNick() == nickname && clients[i] != *it)
        {
			output.insert(std::pair<std::string, std::set<int> >(ERR_NICKNAMEINUSE((*it)->getNick(), (*it)->getNick()), fds));
            return;
        }
    }
	// ? boucle pour parcourir vector client et verifier doublons nick client ?
	// if (nickname == (*it)->getNick())
	// {
	// 	output.insert(std::pair<std::string, std::set<int> >(ERR_NICKNAMEINUSE((*it)->getNick(), (*it)->getNick()), fds));
	// 	return ;
	// }
	// if ((*it)->getUse() == false)
	// 	(*it)->setNick(nickname);
	// else
	// {
	// 	(*it)->setNick(nickname);
	// 	output.insert(std::pair<std::string, std::set<int> >(RPL_CHGENICK(nickname), fds));
	// }
	(*it)->setNick(nickname);
	std::cout << "NICKNAME: " << (*it)->getNick() << std::endl;
}
