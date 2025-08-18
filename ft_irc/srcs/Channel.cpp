#include "../include/Channel.hpp"

Channel::Channel() : _name(""), _password(""), _topic(""), _topicRestrictions(false), _isInvited(false), _userLimit(-1), _clients(), _invited()
{
	std::cout << "Channel constructor called" << std::endl;
}

Channel::Channel(std::string const &name) : _name(name)
{
	;
}
Channel::Channel(Channel const &obj) : _name(obj._name), _password(obj._password), _topic(obj._topic), _topicRestrictions(obj._topicRestrictions), _isInvited(obj._isInvited), _userLimit(obj._userLimit), _clients(obj._clients), _invited(obj._invited)
{
	;
}

Channel &Channel::operator=(Channel const &obj)
{
	this->_name = obj._name;
	this->_password = obj._password;
	this->_topic = obj._topic;
	this->_topicRestrictions = obj._topicRestrictions;
	this->_isInvited = obj._isInvited;
	this->_userLimit = obj._userLimit;
	this->_clients = obj._clients;
	this->_invited = obj._invited;
	return (*this);
}

Channel::~Channel()
{
	std::cout << "Channel destructor called" << std::endl;
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

bool Channel::getTopicRestrictions(void) const
{
	return (_topicRestrictions);
}

bool	Channel::getInvited(void) const
{
	return (_isInvited);
}

int	Channel::getLimit(void) const
{
	return (_userLimit);
}

int	Channel::getNbUsers(void) const
{
	return (static_cast<int>(_clients.size()));
}

void Channel::setName(std::string const &name)
{
	_name = name;
}

void	Channel::setPassword(std::string const &password)
{
	_password = password;
}

bool	Channel::setTopic(std::string const &topic, std::string const &username)
{
	std::map<std::string, int>::iterator it = _clients.find(username);

	if (it != _clients.end())
	{
		if (it->second == OPERATOR)
		{
			_topic = topic;
			return (true);
		}
	}
	return (false);
}

void Channel::setInvited(std::string const &client)
{
	_invited.push_back(client);
}

int Channel::isChannelCommand(const char *str)
{
	std::cout << "STR === " << str << std::endl;
	int			i;
	int			channelCommand_found;
	const char	*channelCommand[] = {"USER", "PASS", "NICK", "KICK", "INVITE", "MODE", "TOPIC", NULL};

	i = 0;
	channelCommand_found = -1;
	while (channelCommand[i] != NULL)
	{
		if (strcmp(channelCommand[i], str) == 0)
		{
			channelCommand_found = i;
			std::cout << "command found: " << channelCommand_found << std::endl;
			break ;
		}
		i++;
	}
	return (channelCommand_found);
}

bool Channel::isValid(std::string const &str)
{
	for (size_t i = 1; i < str.length(); i++)
	{
		if (str[i] <= ' ' || str[i] == ';')
		{
			return (false);
		}
	}
	return (true);
}

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

void Channel::addChannel(Channel &channel)
{
	_channels[channel.getName()] = &channel;
}

bool Channel::isInvited(std::string const &client)
{
	for (size_t i = 0; i < _invited.size(); i++)
	{
		if (_invited[i] == client)
		{
			return (true);
		}
	}
	return (false);
}

bool Channel::isClientInChannel(std::string const &username)
{
	std::map<std::string, int>::iterator it = _clients.find(username);

	if (it != _clients.end())
	{
		return (true);
	}
	return (false);
}

// void Channel::addClient(Client *client)
// {
// 	if (!isClientInChannel(client->getName()))
// 	{
// 		_clients[client->getName()] = MEMBER;
// 	}
// }

void Channel::removeClient(std::string const &username)
{
	std::map<std::string, int>::iterator it = _clients.find(username);

	if (it != _clients.end())
	{
		_clients.erase(username);
	}
}

std::string Channel::getClient(std::string const &username) const
{
	std::map<std::string, int>::const_iterator it = _clients.find(username);

	if (it != _clients.end())
	{
		return (it->first);
	}
	std::cerr << "Error: Client " << username << " not found" << std::endl;
	return ("");
}

std::vector<std::string> Channel::getClients(void) const
{
	std::vector<std::string> clients;
	std::map<std::string, int>::const_iterator it = _clients.begin();

	for ( ; it != _clients.end(); it++)
	{
		clients.push_back(it->first);
	}
	return (clients);
}

Channel& Channel::getChannelByName(std::string const &name)
{
	static std::map<std::string, Channel> channels;

	if (channels.empty())
	{
		channels.insert(std::make_pair("#general", Channel("#general")));
		channels.insert(std::make_pair("#random", Channel("#random")));
	}

	std::map<std::string, Channel>::iterator it = channels.find(name);
	if (it == channels.end())
	{
		throw std::runtime_error("Channel " + name + " not found");
		//std::cout << ERR_NOSUCHCHANNEL(user, channel.getName()) << std::endl;
		//return (NULL);
	}
	return (it->second);
}

// // MODES
// bool Channel::modeI(std::string const &client, std::string const &arg)
// {
// 	std::map<std::string, int>::iterator it = _clients.find(client);

// 	if (it != _clients.end() && it->second == OPERATOR)
// 	{
// 		if (arg == "+i")
// 		{
// 			_isInvited = true;
// 			// getClientByName(clientName)->sendMessage(RPL_CHANNELMODEIS(clientName, _name, "+i"));
// 		}
// 		else
// 		{
// 			_isInvited = false;
// 			// getClientByName(clientName)->sendMessage(RPL_CHANNELMODEIS(clientName, _name, "-i"));
// 		}
// 	}
// 	else
// 	{
// 		return (false);
// 	}
// 	return (true);
// }

// bool Channel::modeK(std::string const &client, std::string const &arg, std::string const &password)
// {
// 	std::map<std::string, int>::iterator it = _clients.find(client);

// 	if (it != _clients.end() && it->second == OPERATOR)
// 	{
// 		if (arg == "+k")
// 		{
// 			_password = password;
// 		}
// 		else
// 		{
// 			if (_password != password)
// 			{
// 				return (false);
// 			}
// 			else
// 			{
// 				_password.erase();
// 			}
// 		}
// 	}
// 	else
// 	{
// 		return (false);
// 	}
// 	return (true);
// }

// bool Channel::modeL(std::string const &client, std::string const &arg, int const &limit)
// {
// 	std::map<std::string, int>::iterator it = _clients.find(client);

// 	if (it != _clients.end() && it->second == OPERATOR)
// 	{
// 		if (arg == "+l")
// 		{
// 			_userLimit = limit;
// 		}
// 		else
// 		{
// 			_userLimit = -1;
// 		}
// 	}
// 	else
// 	{
// 		return (false);
// 	}
// 	return (true);
// }

// bool Channel::modeO(std::string const &client, std::string const &arg, std::string const &target)
// {
// 	std::map<std::string, int>::iterator it = _clients.find(client);
// 	std::map<std::string, int>::iterator ite = _clients.find(target);

// 	if (it != _clients.end() && it->second == OPERATOR && ite->second != OPERATOR)
// 	{
// 		if (arg == "+o")
// 		{
// 			ite->second = OPERATOR;
// 		}
// 		else
// 		{
// 			ite->second = MEMBER;
// 		}
// 	}
// 	else
// 	{
// 		return (false);
// 	}
// 	return (true);
// }

// bool Channel::modeT(std::string const &client, std::string const &arg)
// {
// 	std::map<std::string, int>::iterator it = _clients.find(client);

// 	if (it != _clients.end() && it->second == OPERATOR)
// 	{
// 		if (arg == "+t")
// 		{
// 			_topicRestrictions = true;
// 		}
// 		else
// 		{
// 			_topicRestrictions = false;
// 		}
// 	}
// 	else
// 	{
// 		return (false);
// 	}
// 	return (true);
// }
