#include "../../include/Kick.hpp"

Kick::Kick()
{
	;
}

Kick::Kick(Kick const &obj)
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

void Kick::execute(std::string const &command, Client &client, Channel &channel, std::string const &args)
{
	std::cout << "Entering " << command << " command" << std::endl;
	std::stringstream ss(args);
	std::string word;
	int count = 0;

	while (ss >> word)
	{
		count++;
	}
	if (count < 2 || count > 3)
	{
		std::cout << ERR_NEEDMOREPARAMS(client.getNick());
		return ;
	}

	ss.clear();
	ss.seekg(0);

	std::string channelName;
	std::string user;
	std::string comment;
	ss >> channelName >> user >> comment;

	std::cout << "channelName: " << channelName << std::endl;
	std::cout << "user: " << user << std::endl;
	std::cout << "comment: " << comment << std::endl;

	//ERR_NOSUCHCHANNEL(user, channel.getName()); cf CHANNEL.cpp
	// Channel *channel = Channel::getChannelByName(channelName);
	// if (!channel)
	// {
		// std::cerr << "Error: no such channel " << channelName << std::endl;
		// std::cout << ERR_NOSUCHCHANNEL(user, channelName) << std::endl;
		// return;
	// }
	if (!channel.isClientInChannel(user))
	{
		std::cerr << "Error: user " << user << " not in channel" << std::endl;
		std::cerr << ERR_USERNOTINCHANNEL(user, channel.getName()) << std::endl;
		return ;
	}
	//channel.removeClient(user);
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
