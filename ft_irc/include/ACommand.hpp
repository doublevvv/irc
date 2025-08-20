#ifndef ACOMMAND_HPP
# define ACOMMAND_HPP

#include "Client.hpp"
#include "Channel.hpp"

class Client;

class Channel;

class ACommand
{
	public:
		ACommand();
		ACommand(ACommand const &obj);
		ACommand	&operator=(ACommand const &obj);
		virtual ~ACommand();

		virtual void execute(std::string const &command, Client &client, const std::string &args) = 0;
};

#endif
