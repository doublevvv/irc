#ifndef KICKCOMMAND_HPP
#define KICKCOMMAND_HPP

#include "AChannelCommand.hpp"
#include "Channel.hpp"
#include "Errors.hpp"
#include "Replies.hpp"

class Channel;

class KickCommand : public AChannelCommand
{
	public:
		KickCommand();
		KickCommand(KickCommand const &obj);
		KickCommand	&operator=(KickCommand const &obj);
		virtual ~KickCommand();

		virtual void execute(std::string const &command, std::string const &args);
		virtual void executeCmd(Channel& channel, std::string const &user, std::string const &args);
};

#endif
