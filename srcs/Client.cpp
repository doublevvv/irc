/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doublevv <vv>                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 18:53:23 by doublevv          #+#    #+#             */
/*   Updated: 2025/08/16 14:39:11 by doublevv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/client.hpp"

// Client::Client() : _fd_client(0)
// {

// }

Client::Client(int fd, std::string ip_add) : _fd_client(fd), _ip_add(ip_add)
{

}

Client::~Client()
{

}

Client::Client(const Client &obj)
{
	this->_nickname = obj._nickname;
	this->_username = obj._username;
	this->_password = obj._password;
	this->_realname = obj._realname;
}

Client& Client::operator=(const Client &rhs)
{
	_nickname = rhs._nickname;
	_username = rhs._username;
	_password = rhs._password;
	_realname = rhs._realname;
	return (*this);

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

std::string Client::getNick()
{
	return (this->_nickname);
}
std::string Client::getUser()
{
	return (this->_username);
}
std::string Client::getPass()
{
	return (this->_password);
}

std::string Client::getReal()
{
	return (this->_realname);
}

