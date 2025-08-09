#ifndef SERVER_HPP
#define SERVER_HPP

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

#define PORT 4242

class Server
{
	public:
	Server();
	~Server();
	bool	initServer();
	bool	checkPoll();
	bool	newClient();
	bool	newData();

	private:
	int _fdserver;
	int _newfdclient;
	pollfd fds[SOMAXCONN];
	struct sockaddr_in sa; //* structure de donnees de la socket
	int	_fdcount;
	std::vector<Server> fd_arr;
};

#endif
