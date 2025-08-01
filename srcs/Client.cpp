/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doublevv <vv>                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 18:53:23 by doublevv          #+#    #+#             */
/*   Updated: 2025/07/15 11:53:50 by doublevv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ClientServer.hpp"

/*
		CLIENT:
	1) creation d'une socket, retourne un numero de descripteur "SOCKET"
	2) connexion de la socket a un serveur distant "CONNECT"
	3) envoyer des donnees via la socket "SEND"
	4) recevoir les donnees "RECV"
	5) modifie simplement permissions de lecture et d’écriture de la socket "SHUTDOWN"
	5) fermer la socket "CLOSE"
*/

// int	socket(int domain, int type, int protocol)
// {
// 	domain = AF_INET6;
// 	type = SOCK_STREAM; // *envois successifs d'informations s'additionnent, il n'y a pas de "séparations" entre elles
// 	protocol = 0;
// }

// int	connect(int fd, const struct sockaddr *serv_addr, socklen_t addrlen)
// {
// 	//* serv_addr = pointeur vers struct qui contient infos de co. sockaddr_in pour une adresse IPv4
// }

// int	send(int fd, char *buffer, int len, int options)
// {

// }

// int	recv(int fd, void *buffer, int len, int flags)
// {
// 	// * buffer = points to a buffer where the message should be stored
// 	// * flags = type of message reception
// }

// int shutdown(int fd, int how)
// {
// 	// * how = entier qui contient des drapeaux qui indiquent comment fermer la socket
// }

// int close(int fd)
// {

// }

//------------------------------------------------------------------------------------

int	Client::get_fd(void)
{
	return (this->_fd_client);
}

void	Client::set_fd(int fd)
{
	this->_fd_client = fd;
}

int	Client::crea_client(std::string arg)
{
	Client client;
	struct sockaddr_in sa;
	char buffer[BUFSIZ];
	int bytes_read;
	std::string msg;
	int msg_len;
	int bytes_sent;

	memset(&sa, 0, sizeof sa);
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	sa.sin_port = htons(PORT);

	client._fd_client = socket(sa.sin_family, SOCK_STREAM, 0);
	if (client._fd_client == -1)
	{
		throw(std::invalid_argument("invalid socket\n"));
		return (1);
	}
	std::cout << "socket created" << std::endl;
	client._status = connect(client._fd_client, (struct sockaddr *)&sa, sizeof sa);
	if (client._status == -1)
	{
		throw(std::invalid_argument("invalid status\n"));
		return (1);
	}
	msg = arg;
	msg_len = arg.size();
	bytes_sent = send(client._fd_client, msg.c_str(), msg_len, 0);
	if (bytes_sent == -1)
	{
		throw(std::invalid_argument("send error\n"));
		return (1);
	}
	else if (bytes_sent == msg_len)
	{
		std::cout << "full msg ok" << std::endl;
	}
	bytes_read = 1;
	while (bytes_read >= 0)
	{
		bytes_read = recv(client._fd_client, buffer, BUFSIZ, 0);
		if (bytes_read == -1)
		{
			std::cout << "error recv" << std::endl;
		}
		else
		{
			buffer[bytes_read] = '\0';
			std::cout << "msg received: %s\n" << buffer;
			break;
		}
	}
	std::cout << "closing socket client" << std::endl;
	close(client._fd_client);
	return (0);
}
