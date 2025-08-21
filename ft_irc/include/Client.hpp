#ifndef CLIENT_HPP
# define CLIENT_HPP

#include "Channel.hpp"
#include <iostream>
#include <arpa/inet.h>
#include <bits/stdc++.h>
#include <cstdio>
#include <cstdlib>
#include <csignal>
#include <cstring>
#include <errno.h>
#include <netdb.h> // * acceder a struct hostent (infos machines hote)
#include <netinet/in.h> // * library for ipv6
#include <poll.h>
#include <string>
#include <strings.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <vector>
#include <map>

enum e_userCommands {
	USER,
	PASS,
	NICK,
	PRIVMSG,
	CAP
};

class Channel;

class Client
{
	public:
		Client();
		Client(int fd);
		Client(Client const &obj);
		Client	&operator=(Client const &obj);
		~Client();

		int const &getFd(void) const;
		std::string const &getNick() const;
		std::string const &getUser() const;
		std::string const &getPass() const;
		std::string const &getReal() const;
		std::string const &getIp() const;
		bool getUse();
		// void sendMessage(std::string const &message);

		void setNick(std::string);
		void setUser(std::string);
		void setPass(std::string);
		void setReal(std::string);
		void setIp(std::string);
		void setUse(bool used);
		void setFd(int fd);

		void	execute(std::string const &command, std::string const &args);
		void	executeCmd(std::string const &command, std::string, int, char, std::string);
		void	executePWD(std::string const &command, std::string const &args);
		void	executePWDCmd(std::string const &command, std::string password);
		void	executeNick(std::string const &command, std::string const &args);
		void	executeNickCmd(std::string nickname);
		void	executePrivmsg(std::string const &command, std::string const &args);
		void	executePrivmsgCmd(std::string target, std::string message);
		void	executeCap(std::string const &command, std::string const &args);

		bool	checkNickname(std::string nickname);
		void	sendMsgtoClient(int fd, std::string msg);
		int	isClientCommand(char *str);

	private:
		int _fd_client;
		std::string	_nickname;
		std::string _username;
		std::string _realname;
		std::string _password;
		std::string _ip_add;
		std::vector<std::string> nckn;
		int _status; //* si admin ou pas (membres ou operator)
		bool	_used;

		// *buffer d'entree et de sortie
		//* si \n, erase

};

#endif
