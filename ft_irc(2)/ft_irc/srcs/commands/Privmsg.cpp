#include "../../include/Privmsg.hpp"
#include "../../include/ACommand.hpp"

Privmsg::Privmsg()
{
	;
}

Privmsg::Privmsg(Privmsg const &obj) : ACommand(obj)
{
	(void)obj;
}

Privmsg& Privmsg::operator=(Privmsg const &obj)
{
	(void)obj;
	return (*this);
}

Privmsg::~Privmsg()
{
	;
}

void	Privmsg::execute(Server &server, std::string const &command, std::vector<Client*>::iterator it, std::string const &args)

{
	std::cout << "Entering " << command << " command" << std::endl;
	std::stringstream ss(args);
	std::string word;
	int count = 0;
	std::map<std::string, std::set<int> > &output = server.getOutput();
	std::set<int> fds;
	fds.insert((*it)->getFd());

	while (ss >> word)
	{
		count++;
	}
	if (count != 2)
	{
		output.insert(std::pair<std::string, std::set<int> >(ERR_NEEDMOREPARAMS((*it)->getNick()), fds));
		return ;
	}
	ss.clear();
	ss.seekg(0);
	std::string target;
	std::string msg;
	ss >> target >> msg;

	// * cannot send to chan
	// ? user away ?
	if (target[0] == '#')
	{
		target.erase(0, 1);
		std::cout << "TARGET = " << target << std::endl;
		output.insert(std::pair<std::string, std::set<int> >(msg, fds));
	}
	else
	{
		std::vector<Client*> client = server.getClientId();
		std::vector<Client*>::iterator it;
		for (it = client.begin(); it != client.end(); ++it)
		{
			std::cout << "PRISG vector: " << (*it)->getNick() << std::endl;
			if ((*it)->getNick() == target)
			{
				std::set<int> fds;
				fds.insert((*it)->getFd());
				std::cout << "HEREEEEEEE\n";
				output.insert(std::pair<std::string, std::set<int> >(msg, fds));
				return ;
			}
			else
			{
				output.insert(std::pair<std::string, std::set<int> >(ERR_NOSUCHNICK((*it)->getNick(), target), fds));
				return ;
			}
		}
	}
}
