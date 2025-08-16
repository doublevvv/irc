#include "user.hpp"
#include "client.hpp"
#include "../include/errors.hpp"

UserCommand::UserCommand() : _used(false)
{

}

UserCommand::~UserCommand()
{

}
bool	UserCommand::getUse()
{
	return (this->_used);
}

void	UserCommand::execute(std::string const &command, std::string const &args)
{
	std::cout << "Entering " << command << " command" << std::endl;
	std::stringstream ss(args);
	std::string username;
	int mode;
	char unused;
	std::string realname;
	ss >> username >> mode >> unused >> realname;

	std::cout << "" << username << "" << mode << "" << unused << ":" << realname << std::endl;
	executeCmd(command, username, mode, unused, realname);
}

void	UserCommand::executeCmd(std::string const &command, std::string usern, int mode, char unused, std::string realn)
{
	Client client;

	if (!usern.empty())
		client.setUser(usern);
	if (!realn.empty())
	client.setReal(realn);
	if (_used == true)
		std::cout << ERR_ALREADYREGISTERED(usern);
	if (usern.empty() || mode == NULL || unused == NULL || realn.empty())
		std::cout << ERR_NEEDMOREPARAMS(usern, command);
	if (mode != '0')
		std::cout << ":" << command << "arg mode must be zero\n";
	if (unused != '*')
		std::cout << ":" << command << "arg between mode and realname must be a asterix\n";
	_used = true;
}
