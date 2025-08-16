#include "privmsg.hpp"
#include "client.hpp"
#include "../include/errors.hpp"
#include "user.hpp"

PrivmsgCommand::PrivmsgCommand()
{

}

PrivmsgCommand::~PrivmsgCommand()
{

}

void	PrivmsgCommand::execute(std::string const &command, std::string const &args)
{
	std::cout << "Entering " << command << " command" << std::endl;
	std::stringstream ss(args);
	std::string target;
	std::string msg;
	ss >> target >> msg;

	std::cout << "" << target << "" << msg << std::endl;
	executeCmd(target, msg);
}
void	PrivmsgCommand::executeCmd(std::string target, std::string msg)
{
	
}
