#include "../include/Channel.hpp"

Channel::Channel() : _name(""), _password(""), _topic(""), _topicRestrictions(false), _isInviteOnly(false), _userLimit(-1), _clients(), _invited()
{
	;
}

Channel::Channel(std::string const &name) : _name(name), _password(""), _topic(""), _topicRestrictions(false), _isInviteOnly(false), _userLimit(-1), _clients(), _invited()
{
	;
}

Channel::Channel(Channel const &obj) : _name(obj._name), _password(obj._password), _topic(obj._topic), _topicRestrictions(obj._topicRestrictions), _isInviteOnly(obj._isInviteOnly), _userLimit(obj._userLimit), _clients(obj._clients), _invited(obj._invited)
{
	;
}

Channel &Channel::operator=(Channel const &obj)
{
	this->_name = obj._name;
	this->_password = obj._password;
	this->_topic = obj._topic;
	this->_topicRestrictions = obj._topicRestrictions;
	this->_isInviteOnly = obj._isInviteOnly;
	this->_userLimit = obj._userLimit;
	this->_clients = obj._clients;
	this->_invited = obj._invited;
	return (*this);
}

Channel::~Channel()
{
	;
}

std::string const &Channel::getName(void) const
{
	return (_name);
}

std::string const &Channel::getPassword(void) const
{
	return (_password);
}

std::string	const &Channel::getTopic(void) const
{
	return (_topic);
}

bool Channel::isTopicRestricted(void) const
{
	return (_topicRestrictions);
}

bool	Channel::isInviteOnly(void) const
{
	return (_isInviteOnly);
}

int	Channel::getLimit(void) const
{
	return (_userLimit);
}

int	Channel::getNbUsers(void) const
{
	return (static_cast<int>(_clients.size()));
}

void Channel::setName(std::string &name)
{
	_name = name;
}

void	Channel::setPassword(std::string &password)
{
	_password = password;
}

void Channel::setTopic(std::string const &topic)
{
	_topic = topic;
}

void Channel::setLimit(int &limit)
{
	_userLimit = limit;
}

void Channel::setInvited(std::string const &client)
{
	_invited.push_back(client);
}

bool Channel::isInvited(std::string const &nickname)
{
	std::map<std::string, int>::iterator it = _clients.find(nickname);

	if (it != _clients.end())
	{
		return (true);
	}
	return (false);
}

bool Channel::isClientInChannel(std::string const &nickname)
{
	std::map<std::string, int>::iterator it = _clients.find(nickname);

	if (it != _clients.end())
	{
		return (true);
	}
	return (false);
}

void Channel::addClientToChannel(Client* client)
{
	_clients[client->getNick()] = client->getStatus();
}

void Channel::addInvitedClient(Client *client)
{
	_invited.push_back(client->getNick());
}

void Channel::removeClientFromChannel(std::string const &nickname)
{
	_clients.erase(nickname);
}

// MODES
// bool	Channel::modeI(std::string const &client, std::map<std::string, Channel*>::iterator ite, std::string const &arg)
// {
// 	std::map<std::string, int>::iterator it = _clients.find(client);
// 	std::cout << "first: " << it->first << std::endl;
// 	std::cout << "second: " << it->second << std::endl;

// 	if (it == _clients.end())
// 	{
// 		return (false);
// 	}
// 	if (it->second != OPERATOR)
// 	{
// 		return (false);
// 	}
// 	if (arg == "+i")
// 	{
// 		_isInviteOnly = true;
// 		ite->second->setPassword(password);
// 		std::cout << "_password: " << ite->second->_password << std::endl;
// 	}
// 	else if (arg == "-i")
// 	{
// 		_isInviteOnly = false;
// 	}
// 	return (true);
// }

bool Channel::modeK(std::string const &client, std::map<std::string, Channel*>::iterator ite, std::string const &arg, std::string &password)
{
	std::map<std::string, int>::iterator it = _clients.find(client);

	std::cout << "first: " << it->first << std::endl;
	std::cout << "second: " << it->second << std::endl;

	std::cout << "password: " << password << std::endl;
	std::cout << "channel password: " << _password << std::endl;

	if (it == _clients.end())
	{
		return (false);
	}
	if (it->second != OPERATOR)
	{
		return (false);
	}
	if (arg == "+k")
	{
		ite->second->setPassword(password);
		std::cout << "_password: " << ite->second->_password << std::endl;
	}
	else
	{
		if (ite->second->getPassword() != password)
		{
			return (false);
		}
		else
		{
			std::cout << "_password" << password << std::endl;
			ite->second->_password.erase();
		}
	}
	return (true);
}

// bool Channel::modeL(std::string const &client, std::map<std::string, Channel*>::iterator ite, std::string const &arg, int &limit)
// {
// 	std::map<std::string, int>::iterator it = _clients.find(client);

// 	if (it == _clients.end())
// 	{
// 		return (false);
// 	}
// 	if (it->second != OPERATOR)
// 	{
// 		return (false);
// 	}
// 	if (arg == "+l")
// 	{
// 		ite->second->setLimit(limit);
// 		std::cout << "limit: " << ite->second->_userLimit << std::endl;
// 	}
// 	else
// 	{
// 		ite->second->setLimit(limit);
// 	}
// 	return (true);
// }

// bool Channel::modeO(std::string const &client, std::map<std::string, Channel*>::iterator ite, std::string const &arg, std::string &targetUser)
// {
// 	std::map<std::string, int>::iterator it = _clients.find(client);
// 	std::map<std::string, int>::iterator ite = _clients.find(targetUser);

// 	if (it == _clients.end() || (ite == _clients.end()))
// 	{
// 		std::cout << "target does not exist" << std::endl;
// 		return (false);
// 	}
// 	if (it->second != OPERATOR)
// 	{
// 		return (false);
// 	}
// 	if (arg == "+o")
// 	{
// 		ite->second = OPERATOR;
// 	}
// 	else
// 	{
// 		ite->second = MEMBER;
// 	}
// 	return (true);
// }

// bool Channel::modeT(std::string const &client, std::map<std::string, Channel*>::iterator ite, std::string const &arg)
// {
// 	std::map<std::string, int>::iterator it = _clients.find(client);
// 	std::cout << "first: " << it->first << std::endl;
// 	std::cout << "second: " << it->second << std::endl;

// 	if (it == _clients.end())
// 	{
// 		std::cout << "A" << std::endl;
// 		return (false);
// 	}
// 	if (it->second != OPERATOR)
// 	{
// 		std::cout << "B" << std::endl;
// 		return (false);
// 	}
// 	if (arg == "+t")
// 	{
// 		std::cout << "ICI" << std::endl;
// 		_topicRestrictions = true;
// 	}
// 	else
// 	{
// 		std::cout << "LA" << std::endl;
// 		_topicRestrictions = false;
// 	}
// 	return (true);
// }

void Channel::displayMap(void)
{
	std::cout << "----- DISPLAY MAP -----" << std::endl;
	std::map<std::string, int>::iterator	it;

	for(it = _clients.begin(); it != _clients.end(); it++)
	{
		std::cout << "key = " << it->first << " => " << "value = " << it->second << std::endl;
	}
	std::cout << std::endl;
}


bool Channel::isOperator(std::string const &nickname)
{
    std::map<std::string, int>::const_iterator it = _clients.find(nickname);

	if (it == _clients.end())
	{
		return false;
	}
	return (it->second == OPERATOR);
}


// bool Channel::isValid(std::string const &str)
// {
// 	for (size_t i = 1; i < str.length(); i++)
// 	{
// 		if (str[i] <= ' ' || str[i] == ';')
// 		{
// 			return (false);
// 		}
// 	}
// 	return (true);
// }

// void Channel::checkParameterChannel(std::string const &channelName)
// {
// 	if (channelName.empty() == 0)
// 	{
// 		std::cerr << "Error: missing channel name" << std::endl;
// 	}
// 	else if (channelName.length() > 50)
// 	{
// 		std::cerr << "Error: channel name must be with a maximum length of 50" << std::endl;
// 	}
// 	else if (channelName[0] != '#' || channelName[0] != '&')
// 	{
// 		std::cerr << "Error: channel name must begin with a '&' or '#' character" << std::endl;
// 	}
// 	else if (isValid(channelName))
// 	{
// 		std::cerr << "Error: channel name must not contain space or comma" << std::endl;
// 	}
// 	else if (_channels.find(channelName) == _channels.end())
// 	{
// 		std::cout << "Channel " << channelName << " does not exist" << std::endl;
// 	}
// 	else if ((_channels[channelName]->isClientInChannel(client.getNickname())) == false)
// 	{
// 		std::cerr << "Client " << client << " does not exist in channel " << channelName << std::endl;
// 	}
// }

// std::string Channel::getClient(std::string const &username) const
// {
// 	std::map<std::string, int>::const_iterator it = _clients.find(username);

// 	if (it != _clients.end())
// 	{
// 		return (it->first);
// 	}
// 	std::cerr << "Error: Client " << username << " not found" << std::endl;
// 	return ("");
// }
