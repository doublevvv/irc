#include "../include/Server.hpp"
#include "../include/Client.hpp"

Client::Client() :  _nickname(""), _username(""), _realname(""), _password(""), _ip_add(""), _status(-1),  _used(false)
{
	std::cout << "HERRRRE= " << _fd_client << std::endl;
	std::cout << "Client constructor called" << std::endl;
}

Client::Client(int fd) : _fd_client(fd)
{

}
Client::Client(const Client &obj)
{
	this->_fd_client = obj._fd_client;
	this->_nickname = obj._nickname;
	this->_username = obj._username;
	this->_realname = obj._realname;
	this->_password = obj._password;
	this->_ip_add = obj._ip_add;
	this->_status = obj._status;
	this->_used = obj._used;
	this->nckn = obj.nckn;
}

Client &Client::operator=(Client const &obj)
{
	this->_fd_client = obj._fd_client;
	this->_nickname = obj._nickname;
	this->_username = obj._username;
	this->_realname = obj._realname;
	this->_password = obj._password;
	this->_ip_add = obj._ip_add;
	this->_status = obj._status;
	this->_used = obj._used;
	this->nckn = obj.nckn;
	return (*this);
}

Client::~Client()
{
	std::cout << "Client destructor called" << std::endl;
}

int const &Client::getFd() const
{
	return(this->_fd_client);
}
std::string const &Client::getNick() const
{
	return (this->_nickname);
}

std::string const &Client::getUser() const
{
	return (this->_username);
}

std::string const &Client::getPass() const
{
	return (this->_password);
}

std::string const &Client::getReal() const
{
	return (this->_realname);
}

bool Client::getUse()
{
	return (this->_used);
}

std::string const &Client::getIp() const
{
	return (this->_ip_add);
}

void Client::setNick(std::string nickname)
{
	this->_nickname = nickname;
}
void Client::setUser(std::string username)
{
	this->_username = username;
}
void Client::setPass(std::string password)
{
	this->_password = password;
}

void Client::setReal(std::string realname)
{
	this->_realname = realname;
}

void Client::setIp(std::string ipadd)
{
	this->_ip_add = ipadd;
}

void Client::setFd(int fd)
{
	this->_fd_client = fd;
}

void Client::setUse(bool used)
{
	this->_used = used;
}

// void Client::sendMessage(std::string const &message)
// {
// 	std::string formatted = message + "\r\n";
// 	write(_fd, formatted.c_str(), formatted.size());
// }

// int Client::isClientCommand(char *str)
// {
// 	int			i;
// 	int			clientCommand_found;
// 	const char	*clientCommand[] = {"USER", "PASS", "NICK", NULL};

// 	i = 0;
// 	clientCommand_found = -1;
// 	while (clientCommand[i] != NULL)
// 	{
// 		if (strcmp(clientCommand[i], str) == 0)
// 		{
// 			clientCommand_found = i;
// 			std::cout << "command found: " << clientCommand_found << std::endl;
// 			break ;
// 		}
// 		i++;
// 	}
// 	return (clientCommand_found);
// }


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


/*
	Nicknames are non-empty strings with the following restrictions:
    They MUST NOT contain any of the following characters: space (' ', 0x20), comma (',', 0x2C), asterisk ('*', 0x2A), question mark ('?', 0x3F),
		exclamation mark ('!', 0x21), at sign ('@', 0x40).
    They MUST NOT start with any of the following characters: dollar ('$', 0x24), colon (':', 0x3A).
    They MUST NOT start with a character listed as a channel type, channel membership prefix, or prefix listed in the IRCv3 multi-prefix Extension.
    They SHOULD NOT contain any dot character ('.', 0x2E).
	Each user is distinguished from other users by a unique nickname having a maximum length of nine (9) characters.
 */

// void	Client::executePrivmsg(std::string const &command, std::string const &args)
// {
// 	std::cout << "Entering " << command << " command" << std::endl;
// 	std::stringstream ss(args);
// 	std::string target;
// 	std::string message;
// 	ss >> target >> message;

// 	std::cout << "" << target << "-" << message << std::endl;
// 	// 	for (int i = 0; i < idClient.size(); i++)
// 	// {
// 	// 	std::cout << "NICK = " << idClient[i]->getNick() << std::endl;
// 	// }
// 	executePrivmsgCmd(target, message);
// }

// void	Client::executePrivmsgCmd(std::string target, std::string message)
// {
// 	// * use send ?
// 	/*
// 		 command is used to send private messages between users, as well as to send messages to channels.
// 		<target> is the nickname of a client or the name of a channel.
// 	*/
// 	std::vector<std::string>::iterator it;
// 	for (it = nckn.begin(); it != nckn.end(); it++)
// 	{
// 		std::cout << "nick vector: " << (*it) << std::endl;
// 		if ((*it) == target)
// 		{
// 			sendMsgtoClient(getFd(), message);
// 		}
// 	}
// }

// void	Client::sendMsgtoClient(int fd, std::string msg)
// {
// 	if (send(fd, msg.data(), msg.size(), 0) < 0)
// 		std::cout << "send failed : " << strerror(errno) << std::endl;
// }

// void	Client::executeCap(std::string const &command, std::string const &args)
// {
// 	std::cout << "Entering " << command << " command" << std::endl;
// 	std::stringstream ss(args);
// 	std::string subcmd;
// 	ss >> subcmd;

// 	if (subcmd == "LS")
// 		std::cout << "CAP * LS: KICK INVITE TOPIC MODE\n";
// 	// ! propre a IRSSI !
// }


// 	std::cout << "LEN = " << sizeof(read_bytes) << std::endl;
// 	int rc = send(fds[index].fd, buffer, read_bytes, 0);
// 	if (rc < 0)
// 	{
// 		std::cout << "send failed : " << strerror(errno) << std::endl;
// 	}
