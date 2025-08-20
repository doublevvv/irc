// #include "../../include/Topic.hpp"

// Topic::Topic()
// {
// 	;
// }

// Topic::Topic(Topic const &obj)
// {
// 	(void)obj;
// }

// Topic& Topic::operator=(Topic const &obj)
// {
// 	(void)obj;
// 	return (*this);
// }

// Topic::~Topic()
// {
// 	;
// }

// void Topic::execute(std::string const &command, std::string const &args)
// {
// 	std::cout << "Entering " << command << " command" << std::endl;

// 	std::stringstream ss(args);
// 	std::string channelName;
// 	std::string topicSubject;
// 	ss >> channelName >> topicSubject;

// 	std::cout << "channelName: " << channelName << std::endl;
// 	std::cout << "user: " << topicSubject << std::endl;

// 	Channel chan;
// 	Channel& channel = chan.getChannelByName(channelName);
// 	executeCmd(channel, "", topicSubject);
// }

// void Topic::executeCmd(Channel& channel, std::string const &user, std::string const &args)
// {
// 	(void) user;
// 	std::cout << RPL_TOPIC(user(nickname), channel, args) << std::endl; // Ou ?

// 	if (args.empty())
// 	{
// 		std::cout << "Current topic: " << channel.getTopic() << std::endl;
// 	}
// 	else if (args == " ")
// 	{
// 		// effacer le topic
// 	}
// 	else // user must be OPERATOR
// 	{
// 		if (channel.setTopic(args, user))
// 		{
// 			std::cout << user << " changed topic to: " << args << std::endl;
// 		}
// 		else
// 		{
// 			std::cerr << "Error: " << user << " is not allowed to change topic" << std::endl;
// 		}
// 	}
// }
