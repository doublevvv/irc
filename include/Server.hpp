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
#include <sys/epoll.h>
#include <arpa/inet.h>

#define PORT 9000

class Server
{
	public:
	Server();
	~Server();
	bool	initServer();
	bool	checkPoll();
	void	newClient();
	bool	newData(int);
	void	add_epoll(int epoll_fd, int fd, int events);
	void	addClients();
	void	deleteClients(int i);

	private:
	int _fdserver;
	int _newfdclient;
	int	_epollfd;
	pollfd fds[SOMAXCONN];
	struct sockaddr_in sa; //* structure de donnees de la socket
	int	_fdcount;
	std::vector<pollfd> clienfds;
};

#endif
