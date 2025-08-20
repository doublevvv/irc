#ifndef KICK_HPP
#define KICK_HPP

#include "../include/AChannel.hpp"
#include "../include/Channel.hpp"
#include "../include/Errors.hpp"
#include "../include/Replies.hpp"

class Channel;

class Kick : public AChannel
{
	public:
		Kick();
		Kick(Kick const &obj);
		Kick	&operator=(Kick const &obj);
		virtual ~Kick();

		virtual void execute(std::string const &command, Client &client, Channel &channel, std::string const &args);
};

#endif
