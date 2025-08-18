#ifndef ACHANNELCOMMAND_HPP
# define ACHANNELCOMMAND_HPP

#include "Channel.hpp"
#include <sstream>

class Channel;

class AChannelCommand
{
	public:
		AChannelCommand();
		AChannelCommand(AChannelCommand const &obj);
		AChannelCommand	&operator=(AChannelCommand const &obj);
		virtual ~AChannelCommand();

		virtual void execute(std::string const &command, std::string const &args) = 0;
		virtual void executeCmd(Channel& channel, std::string const &user, std::string const &args) = 0;
};

#endif
