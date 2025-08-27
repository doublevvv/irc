#include "../../include/Privmsg.hpp"
#include "../../include/ACommand.hpp"
#include "../../include/Channel.hpp"

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
	std::map<std::string, Channel*> &chan = server.getChannels();
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
		// target.erase(0, 1);
		// std::cout << "TARGET = " << target << std::endl;
		for (std::map<std::string, Channel*>::iterator jit = chan.begin(); jit != chan.end(); jit++)
		{
			// if (jit->second->getName() != target)
			// {
			// 	std::map<std::string, int>	listClient = jit->second->getClientList();
			// 	if (listClient.find((*it)->getNick()) == listClient.end())
			// 	{
			// 		output.insert(std::pair<std::string, std::set<int> >(ERR_NOTONCHANNEL((*it)->getNick(), target), fds));
			// 		return ;
			// 	}
			// }
			if (jit->second->getName() == target)
			{
				std::cout <<  "TARGET = " << target << std::endl;
				fds = retrieveClient(server, *chan[target], target);
				for (std::set<int>::iterator op = fds.begin(); op!= fds.end(); op++)
				{
					std::cout << "FDS INSIDE PRIVS = " << (*op) << std::endl;

					output.insert(std::pair<std::string, std::set<int> >(RPL_PRIVMSG((*it)->getNick(), (*it)->getUser(), target, msg), fds));
					return ;
				}
			}
		}
	}
	else
	{
		std::vector<Client*> client = server.getClientId();
		std::vector<Client*>::iterator kit;
		for (kit = client.begin(); kit != client.end(); ++kit)
		{
			std::cout << "PRISG vector: " << (*kit)->getNick() << std::endl;
			if ((*kit)->getNick() == target)
			{
				std::set<int> fds;
				fds.insert((*kit)->getFd());
				std::cout << "HEREEEEEEE\n";
				output.insert(std::pair<std::string, std::set<int> >(msg, fds));
				// dire qui a envoye le mesage it->get nickanme
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
