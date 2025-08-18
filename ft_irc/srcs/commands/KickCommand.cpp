#include "../../include/KickCommand.hpp"

KickCommand::KickCommand()
{
	;
}

KickCommand::KickCommand(KickCommand const &obj)
{
	(void)obj;
}

KickCommand& KickCommand::operator=(KickCommand const &obj)
{
	(void)obj;
	return (*this);
}

KickCommand::~KickCommand()
{
	;
}

void KickCommand::execute(std::string const &command, std::string const &args)
{
	std::cout << "Entering " << command << " command" << std::endl;

	std::stringstream ss(args);
	std::string channelName;
	std::string user;
	std::string comment;
	ss >> channelName >> user >> comment;

	std::cout << "channelName: " << channelName << std::endl;
	std::cout << "user: " << user << std::endl;
	std::cout << "comment: " << comment << std::endl;

	Channel chan;
	Channel &channel = chan.getChannelByName(channelName);
	//ERR_NOSUCHCHANNEL(user, channel.getName()); cf CHANNEL.cpp
	// Channel *channel = Channel::getChannelByName(channelName);
	// if (!channel)
	// {
		// std::cerr << "Error: no such channel " << channelName << std::endl;
		// std::cout << ERR_NOSUCHCHANNEL(user, channelName) << std::endl;
		// return;
	// }
	executeCmd(channel, user, comment);
}

void KickCommand::executeCmd(Channel& channel, std::string const &user, std::string const &args)
{
	if (user.empty())
	{
		std::cerr << "Error: no user to kick" << std::endl;
		return;
	}
	if (!channel.isClientInChannel(user))
	{
		std::cerr << "Error: user " << user << " not in channel" << std::endl;
		std::cerr << ERR_USERNOTINCHANNEL(user, channel.getName()) << std::endl;
		return ;
	}
	channel.removeClient(user);
	// std::cout << user << " kicked " << user << " from " << channel.getName() << std::endl;
	if (args == "")
	{
		std::cout << user << " has been kicked from " << channel.getName() << std::endl;
	}
	else
	{
		std::cout << user << " has been kicked from " << channel.getName() << " because " << args << std::endl;
	}
}
