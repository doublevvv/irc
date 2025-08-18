// #include "../../include/TopicCommand.hpp"

// TopicCommand::TopicCommand()
// {
// 	;
// }

// TopicCommand::TopicCommand(TopicCommand const &obj)
// {
// 	(void)obj;
// }

// TopicCommand& TopicCommand::operator=(TopicCommand const &obj)
// {
// 	(void)obj;
// 	return (*this);
// }

// TopicCommand::~TopicCommand()
// {
// 	;
// }

// void TopicCommand::execute(std::string const &command, std::string const &args)
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

// void TopicCommand::executeCmd(Channel& channel, std::string const &user, std::string const &args)
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
