/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientServer.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doublevv <vv>                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 10:49:08 by doublevv          #+#    #+#             */
/*   Updated: 2025/07/12 15:14:20 by doublevv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENTSERVER_HPP
#define CLIENTSERVER_HPP

#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h> // * acceder a struct hostent (infos machines hote)
#include <netinet/in.h> // * library for ipv6
#include <bits/stdc++.h>

#define PORT 4242

class Client
{
	public:
		Client();
		~Client();
		Client &operator=(const Client &rhs);
		int	get_fd();
		void	set_fd(int fd);
	private:
		int _fd_client;
		int	_status;
};


class Server
{
	public:
		Server();
		~Server();
		Server &operator=(const Server &rhs);
		int create_server(std::string arg);
		int	get_fd();
		void	set_fd(int fd);

	private:
		int _fd_server;
		int	_status;
};

// ! GUETTEUR
#endif
