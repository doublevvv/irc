#include "pass.hpp"
#include "client.hpp"
#include "../include/errors.hpp"
#include "user.hpp"

PassCommand::PassCommand()
{

}

PassCommand::~PassCommand()
{

}

void	PassCommand::execute(std::string const &command, std::string const &args)
{
	std::cout << "Entering " << command << " command" << std::endl;
	std::stringstream ss(args);
	std::string password;
	ss >> password;

	std::cout << "" << password << std::endl;
	executeCmd(command, password);
}

void	PassCommand::executeCmd(std::string const &command, std::string password)
{
	UserCommand user;
	Client client;
	
	if (password.empty())
		std::cout << ERR_NEEDMOREPARAMS(command, password);
	if (user.getUse() == true)
		std::cout << ERR_ALREADYREGISTERED(password);
	else
		client.setPass(password);
}
/*
 A "PASS" command is not required for a client connection to be
   registered, but it MUST precede the latter of the NICK/USER
   combination (for a user connection) or the SERVICE command (for a
   service connection). The RECOMMENDED order for a client to register
   is as follows:

                           1. Pass message
           2. Nick message                 2. Service message
           3. User message

   Upon success, the client will receive an RPL_WELCOME (for users) or
   RPL_YOURESERVICE (for services) message indicating that the
   connection is now registered and known the to the entire IRC network.
   The reply message MUST contain the full client identifier upon which
   it was registered.
*/
