/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientServer.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doublevv <vv>                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 10:49:08 by doublevv          #+#    #+#             */
/*   Updated: 2025/07/08 08:02:03 by doublevv         ###   ########.fr       */
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

class Client
{
	public:
		Client();
		~Client();

		Client &operator=(const Client &rhs);

		//Methods

	protected:

	private:
};


class Server {
	public:
		Server();
		~Server();

		Server &operator=(const Server &rhs);

		//Methods

	protected:

	private:
};

#endif
