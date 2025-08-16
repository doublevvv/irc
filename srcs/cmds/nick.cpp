#include "nick.hpp"
#include "client.hpp"
#include "../include/errors.hpp"
#include "user.hpp"

NickCommand::NickCommand() : _used(false)
{

}

NickCommand::~NickCommand()
{

}

void	NickCommand::execute(std::string const &command, std::string const &args)
{
	std::cout << "Entering " << command << " command" << std::endl;
	std::stringstream ss(args);
	std::string nickname;
	ss >> nickname;

	std::cout << "" << nickname << std::endl;
	executeCmd(nickname);
}

void	NickCommand::executeCmd(std::string nickname)
{
	Client client;
	UserCommand user;

	if (!nickname.empty() && user.getUse() == true)
	{
		client.setNick(nickname);
		// If used after registration, the server will return a NICK message
	}
	else
		std::cout << ERR_NONICKNAMEGIVEN;
	// if (sizeof(nickname) > 9)
		// * couper le nickname apres 9
	for (int i = 0; i <= 9; i++)
	{
		if (nickname[i] == ' ' || nickname[i] == ',' || nickname[i] == '*' || nickname[i] == '?' ||
			nickname[i] == '!' || nickname[i] == '@' || nickname[i] == '.' || nickname[1] == '$' || nickname[i] == ':')
			std::cout << ERR_ERRONEUSNICKNAME(nickname, nickname) << std::endl;
	}
	if (_used == true)
		std::cout << ERR_NICKNAMEINUSE(nickname, nickname);
	_used = true;

}

/*
	Nicknames are non-empty strings with the following restrictions:
    They MUST NOT contain any of the following characters: space (' ', 0x20), comma (',', 0x2C), asterisk ('*', 0x2A), question mark ('?', 0x3F),
		exclamation mark ('!', 0x21), at sign ('@', 0x40).
    They MUST NOT start with any of the following characters: dollar ('$', 0x24), colon (':', 0x3A).
    They MUST NOT start with a character listed as a channel type, channel membership prefix, or prefix listed in the IRCv3 multi-prefix Extension.
    They SHOULD NOT contain any dot character ('.', 0x2E).
	Each user is distinguished from other users by a unique nickname having a maximum length of nine (9) characters.
 */

