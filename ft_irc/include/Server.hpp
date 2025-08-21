#ifndef SERVER_HPP
# define SERVER_HPP

#include "Client.hpp"
#include "Channel.hpp"
#include "Errors.hpp"
#include "Replies.hpp"
#include <arpa/inet.h>
#include <bits/stdc++.h>
#include <cstdio>
#include <cstdlib>
#include <csignal>
#include <cstring>
#include <errno.h>
#include <fcntl.h>
#include <iostream>
#include <netdb.h> // * acceder a struct hostent (infos machines hote)
#include <netinet/in.h> // * library for ipv6
#include <poll.h>
#include <sstream>
#include <strings.h>
#include <stdexcept>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>

extern bool	signalGlobal;

class Client;

class Channel;

class Server
{
	public:
		Server();
		Server(Server const &obj);
		Server	&operator=(Server const &obj);
		~Server();

		void	checkArgs(char *argv[]);
		bool	isValidPort(std::string const &str);
		bool	isValidPassword(std::string const &str);
		static void	sigintHandler(int signal);
		void	setSignal(void);

		void	initServer();
		bool	checkPoll();
		void	newClient();
		bool	newData(int);
		void	addClients();
		void	deleteClients(int i);
		bool	executeUserCommands(char *buffer);
		void	closeFd();
		void	addClientsFD(int);
		int	isClientCommand(const char *str);
		// void	sendMsgtoClient(int fd, std::string msg);

	private:
		int	_port;
		std::string	_password;
		int _fdserver;
		int _newfdclient;
		pollfd fds[SOMAXCONN];
		struct sockaddr_in sa; //* structure de donnees de la socket
		int	_fdcount;
		// std::map<Client*, std::string> mapclient;
		//* vector pour acceder au client et tous ses attributs
		//* map pour chan <std::string, *channel>?
		std::vector<Client*> idClient;
};

#endif
