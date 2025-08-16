#ifndef Client_HPP
#define Client_HPP

#include <iostream>
#include <errno.h>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h> // * acceder a struct hostent (infos machines hote)
#include <netinet/in.h> // * library for ipv6
#include <bits/stdc++.h>
#include <poll.h>
#include <vector>
#include <sys/epoll.h>
#include <arpa/inet.h>

#define PORT 9000

class Client
{
	public:
	Client();
	Client(int, std::string);
	~Client();
	Client(const Client &obj);
	Client &operator=(const Client &rhs);
	void setNick(std::string);
	void setUser(std::string);
	void setPass(std::string);
	void setReal(std::string);
	std::string getNick();
	std::string getUser();
	std::string getPass();
	std::string getReal();

	private:
	int _fd_client;
	std::string _ip_add;
	std::string	_nickname;
	std::string _username;
	std::string _realname;
	int _statut; //* si admin ou pas (membres ou operator)
	std::string _password;

};

#endif
