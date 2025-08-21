#ifndef ACOMMAND_HPP
# define ACOMMAND_HPP

#include "Client.hpp"
#include "Channel.hpp"
#include "Server.hpp"

class Client;

class Channel;

class ACommand
{
	public:
		ACommand();
		ACommand(ACommand const &obj);
		ACommand	&operator=(ACommand const &obj);
		virtual ~ACommand();

		virtual void execute(Server &server, std::string const &command, std::vector<Client*>::iterator it, std::string const &args) = 0;

};

#endif
