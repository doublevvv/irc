// #include "../../include/InviteCommand.hpp"

// InviteCommand::InviteCommand()
// {
// 	;
// }
// InviteCommand::InviteCommand(InviteCommand const &obj)
// {
// 	(void)obj;
// }

// InviteCommand& InviteCommand::operator=(InviteCommand const &obj)
// {
// 	(void)obj;
// 	return (*this);
// }

// InviteCommand::~InviteCommand()
// {
// 	;
// }

// void InviteCommand::execute(std::string const &command, std::string const &args)
// {
// 	std::cout << "Entering " << command << " command" << std::endl;

// 	std::stringstream ss(args);
// 	std::string nickname;
// 	std::string channelName;
// 	ss >> nickname >> channelName;

// 	std::cout << "nickname: " << nickname << std::endl;
// 	std::cout << "channelName: " << channelName << std::endl;

// 	Channel chan;
// 	Channel& channel = chan.getChannelByName(channelName);
// 	executeCmd(channel, nickname, "");
// }

// void InviteCommand::executeCmd(Channel& channel, std::string const &user, std::string const &args)
// {
// 	(void) args;
// 	if (user.empty())
// 	{
// 		std::cerr << "Error: no user to invite" << std::endl;
// 		return;
// 	}
// 	if (channel.isInvited(user))
// 	{
// 		std::cerr << "Error: " << user << " already invited" << std::endl;
// 		return;
// 	}
// 	channel.setInvited(user);
// 	//std::cout << user << " invited " << user << " to " << channel.getName() << std::endl;
// 	std::cout << user << " has been invited to " << channel.getName() << std::endl;
// }
