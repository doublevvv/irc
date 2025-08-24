#include "../../include/Topic.hpp"

Topic::Topic()
{
	;
}

Topic::Topic(Topic const &obj) : ACommand()
{
	(void)obj;
}

Topic& Topic::operator=(Topic const &obj)
{
	(void)obj;
	return (*this);
}

Topic::~Topic()
{
	;
}

void Topic::execute(Server &server, std::string const &command, std::vector<Client*>::iterator it, std::string const &args)
{
	std::cout << "Entering " << command << " command" << std::endl;

	std::stringstream ss(args);
	std::string word;
	int count = 0;

	while (ss >> word)
	{
		count++;
	}
	if (count < 1)
	{
		server.sendMsgtoClient((*it)->getFd(), ERR_NEEDMOREPARAMS((*it)->getNick()));
		return ;
	}

	ss.clear();
	ss.seekg(0);
	std::string channelName;
	std::string topicSubject;
	ss >> channelName >> topicSubject;

	std::cout << "channelName: " << channelName << std::endl;
	std::cout << "user: " << topicSubject << std::endl;

	if (!((*it))->tryJoinChannel())
	{
		return ;
	}
	// Verification si channel existe
	std::map<std::string, Channel*> &channels = server.getChannels();
	std::map<std::string, Channel*>::iterator ite = channels.find(channelName);
	if (ite == channels.end())
	{
		server.sendMsgtoClient((*it)->getFd(), ERR_NOSUCHCHANNEL((*it)->getNick(), channelName));
		return;
	}
	if (topicSubject.empty())
	{
		std::cout << "Current topic: " << ite->second->getTopic() << std::endl;
	}
	else if (topicSubject == " ")
	{
		ite->second->setTopic("");
	}
	else // user must be OPERATOR
	{
		if ((*it)->getStatus() != OPERATOR)
		{
			server.sendMsgtoClient((*it)->getFd(), ERR_CHANOPRIVISNEEDED((*it)->getNick(), channelName));
			return;
		}
		else
		{
			ite->second->setTopic(topicSubject);
			std::cout << (*it)->getNick() << " changed topic to: " << topicSubject << std::endl;
		}
	}
}
