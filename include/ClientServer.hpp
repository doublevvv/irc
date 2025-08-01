/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientServer.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doublevv <vv>                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 10:49:08 by doublevv          #+#    #+#             */
/*   Updated: 2025/08/01 12:59:26 by doublevv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENTSERVER_HPP
#define CLIENTSERVER_HPP

#include <iostream>
#include <errno.h>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h> // * acceder a struct hostent (infos machines hote)
#include <netinet/in.h> // * library for ipv6
#include <bits/stdc++.h>
#include <poll.h>

#define PORT 4242
#define FD_COUNT 5

class Client
{
	public:
		Client(){}
		~Client(){}
		Client &operator=(const Client &rhs);
		int crea_client(std::string arg);
		int	get_fd();
		void	set_fd(int fd);
	private:
		int _fd_client;
		int	_status;
};


class Server
{
	public:
		Server(){}
		~Server(){}
		Server &operator=(const Server &rhs);
		int	get_fd();
		void	set_fd(int fd);
		int create_server(std::string arg);
		int	init_server();
		int	checkPoll();
		int	newclient();

		private:
		int _fd_server;
		int	_status;
};

// ! GUETTEUR
#endif
