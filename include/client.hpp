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
	Client(int, std::string){}
	~Client();

	private:
	int _fd_client;
	std::string	_nickname;
	std::string _username;
	int _statut; //* si admin ou pas (membres ou operator)
	std::string _password;



};

#endif
