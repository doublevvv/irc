#include "../../include/Kick.hpp"

Kick::Kick()
{
	;
}

Kick::Kick(Kick const &obj) : ACommand()
{
	(void)obj;
}

Kick& Kick::operator=(Kick const &obj)
{
	(void)obj;
	return (*this);
}

Kick::~Kick()
{
	;
}

void Kick::execute(Server &server, std::string const &command, std::vector<Client*>::iterator it, std::string const &args)
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
	if (count < 2 || count > 3)
	{
		output.insert(std::pair<std::string, std::set<int> >(ERR_NEEDMOREPARAMS((*it)->getNick()), fds));
		return ;
	}

	ss.clear();
	ss.seekg(0); //ss.str(args);
	std::string channelName;
	std::string user;
	std::string comment;
	ss >> channelName >> user >> comment;
	//std::getline(ss, comment);

	if (!comment.empty() && comment[0] == ' ')
	{
		comment.erase(0, 1);
	}

	std::cout << "channelName: " << channelName << std::endl;
	std::cout << "user: " << user << std::endl;
	std::cout << "comment: " << comment << std::endl;

	if (!((*it))->tryJoinChannel())
	{
		return ;
	}
	// Verification si channel existe
	std::map<std::string, Channel*> &channels = server.getChannels();
	std::map<std::string, Channel*>::iterator ite = channels.find(channelName);
	if (ite == channels.end())
	{
		output.insert(std::pair<std::string, std::set<int> >(ERR_NOSUCHCHANNEL((*it)->getNick(), channelName), fds));
		return;
	}
	// Verification si user a kick est dans le channel
	if (!ite->second->isClientInChannel((*it)->getNick()))
	{
		output.insert(std::pair<std::string, std::set<int> >(ERR_USERNOTINCHANNEL((*it)->getNick(), channelName), fds));
		return ;
	}
	// Verifier que l’emetteur est operateur du channel
	if (!ite->second->isOperator((*it)->getNick()))
	{
		output.insert(std::pair<std::string, std::set<int> >(ERR_CHANOPRIVISNEEDED((*it)->getNick(), channelName), fds));
		return;
	}
	// if ((*it)->getStatus() != OPERATOR)
	// {
	// 	output.insert(std::pair<std::string, std::set<int> >(ERR_CHANOPRIVISNEEDED((*it)->getNick(), channelName), fds));
	// 	return;
	// }

	ite->second->removeClientFromChannel(user);
	server.removeClient(user);
	if (comment.empty())
	{
		std::cout << (*it)->getNick() << " has been kicked from " << channelName << std::endl;
		output.insert(std::pair<std::string, std::set<int> >((*it)->getNick() + " has been kicked from " + channelName + "\n", fds));
	}
	else
	{
		output.insert(std::pair<std::string, std::set<int> >((*it)->getNick() + " has been kicked from " + channelName + " because " + comment +"\n", fds));
	}
}
