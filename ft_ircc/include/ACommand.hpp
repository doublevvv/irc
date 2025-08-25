#ifndef ACOMMAND_HPP
# define ACOMMAND_HPP

#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"

class Server;

class Client;

class Channel;

class ACommand
{
	public:
		virtual ~ACommand() {};

		virtual void execute(Server &server, std::string const &command, std::vector<Client*>::iterator it, std::string const &args) = 0;

};

#endif
