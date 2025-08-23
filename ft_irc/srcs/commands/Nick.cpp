#include "../../include/Nick.hpp"

Nick::Nick()
{
	;
}

Nick::Nick(Nick const &obj)
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
		count++;
	}
	if (count < 0)
	{
		output.insert(std::pair<std::string, std::set<int> >(ERR_NEEDMOREPARAMS((*it)->getNick()), fds));
		return ;
	}
	ss.clear();
	ss.seekg(0);
	std::string nickname;
	ss >> nickname;
	if (nickname.size() > 10)
	{
		std::cout << "NICK: max length for nickname is 9\n";
		return ;
		// ! return here, must nt go in the setnick function
	}
	for (unsigned int i = 0; i < nickname.size(); i++)
	{
		if (nickname[1] == ' ' || nickname[i] == ' ' || nickname[i] == ',' || nickname[i] == '*' || nickname[i] == '?' ||
			nickname[i] == '!' || nickname[i] == '@' || nickname[i] == '.' || nickname[i] == '$' || nickname[i] == ':')
		{
			output.insert(std::pair<std::string, std::set<int> >( ERR_ERRONEUSNICKNAME((*it)->getNick(), (*it)->getNick()), fds));
			return ;
		}
	}
	if ((*it)->getUse() == false)
	{
		(*it)->setNick(nickname); // * pas besoin
		// If used after registration, the server will return a NICK message
	}
	// if (checkNickname(nickname) == true)
	// {
	// 	nckn.push_back(nickname);
	// 	std::cout << "nickname changed to : " << nickname << std::endl;

	// }
	// if (_used == true)
	// 	std::cout << ERR_NICKNAMEINUSE(nickname, nickname);
	// vector de nickname pou le comparer entre eux et verifier qu'il n'y a aps de doublons
	std::cout << "NICKNAME: " << (*it)->getNick() << std::endl;
}
