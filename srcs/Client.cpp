/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doublevv <vv>                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 18:53:23 by doublevv          #+#    #+#             */
/*   Updated: 2025/07/07 19:13:02 by doublevv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientServer.hpp"

/*
		CLIENT:
	1) creation d'une socket, retourne un numero de descripteur "SOCKET"
	2) connexion de la socket a un serveur distant "CONNECT"
	3) envoyer des donnees via la socket "SEND"
	4) recevoir les donnees "RECV"
	5) modifie simplement permissions de lecture et d’écriture de la socket "SHUTDOWN"
	5) fermer la socket "CLOSE"
*/

int	socket(int domain, int type, int protocol)
{
	domain = AF_INET6;
	type = SOCK_STREAM; // *envois successifs d'informations s'additionnent, il n'y a pas de "séparations" entre elles
	protocol = 0;
}

int	connect(int fd, const struct sockaddr *serv_addr, socklen_t addrlen)
{
	//* serv_addr = pointeur vers struct qui contient infos de co. sockaddr_in pour une adresse IPv4
}

int	send(int fd, char *buffer, int len, int options)
{

}

int	recv(int fd, void *buffer, int len, int flags)
{
	// * buffer = points to a buffer where the message should be stored
	// * flags = type of message reception
}

int shutdown(int fd, int how)
{
	// * how = entier qui contient des drapeaux qui indiquent comment fermer la socket
}

int close(int fd)
{

}
