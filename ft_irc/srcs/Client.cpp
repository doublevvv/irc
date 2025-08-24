#include "../include/Server.hpp"
#include "../include/Client.hpp"

Client::Client() : _nickname(""), _username(""), _realname(""), _password(""), _ip_add(""), _status(-1), _used(false), _registered(false)
{
	std::cout << "HERRRRE= " << _fd_client << std::endl;
	std::cout << "Client constructor called" << std::endl;
}

Client::Client(int fd) : _fd_client(fd), _nickname(""), _username(""), _realname(""), _password(""), _ip_add(""), _status(-1), _used(false), _registered(false)
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
	this->_registered = obj._registered;
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
	this->_registered = obj._registered;
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

std::string const &Client::getIp() const
{
	return (this->_ip_add);
}

int &Client::getStatus(void)
{
	return (this->_status);
}

bool Client::getUse()
{
	return (this->_used);
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

void Client::setUse(bool used)
{
	this->_used = used;
}

void Client::setFd(int fd)
{
	this->_fd_client = fd;
}

void Client::setStatus(int status)
{
	this->_status = status;
}

bool Client::tryRegister(void)
{
	if (!_password.empty())
	{
		if (!_registered)
		{
			_registered = true;
			std::cout << "Client " << _nickname << " registered" << std::endl;
		}
	}
	else
	{
		std::cout << "Client " << _nickname << " must first register with the 'PASS' command" << std::endl;
		return (false);
	}
	return (true);
}

bool Client::isRegistered(void)
{
	return (_registered);
}

bool Client::tryJoinChannel(void)
{
	if (!_password.empty() && !_nickname.empty() && !_username.empty())
	{
		_registered = true;
		std::cout << "Client " << _nickname << " registered" << std::endl;
	}
	else
	{
		std::cerr << "Client " << _nickname << " must register to access to channels" << std::endl;
		return (false);
	}
	return (true);
}

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

