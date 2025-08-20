#ifndef ACHANNEL_HPP
# define ACHANNEL_HPP

#include "Channel.hpp"
#include <sstream>

class Channel;

class AChannel
{
	public:
		AChannel();
		AChannel(AChannel const &obj);
		AChannel	&operator=(AChannel const &obj);
		virtual ~AChannel();

		virtual void execute(std::string const &command, Client &client, Channel &channel, std::string const &args) = 0;
};

#endif
