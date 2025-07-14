/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doublevv <vv>                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:25:45 by doublevv          #+#    #+#             */
/*   Updated: 2025/07/14 14:14:02 by doublevv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientServer.hpp"

/*
		SERVER:
	1) creation d'une socket, retourne un numero de descripteur "SOCKET"
	2) associer une socket, specifier type de communication associe au socket (TCP) "BIND"
	3) ecouter un port, pls connexions sur un meme port "LISTEN"
	4) accepter un connexion "ACCEPT"
	> bloque un attendnat connexion client
	5) recevoir les donnees "RECV" : requete
	6) renvoie les donnes "SEND" : reponse
	7) modifie simplement permissions de lecture et d’écriture de la socket "SHUTDOWN"
	8) fermer la socket "CLOSE"
*/

int	socket(int domain, int type, int protocol)
{
	domain = AF_INET6;
	type = SOCK_STREAM; // *envois successifs d'informations s'additionnent, il n'y a pas de "séparations" entre elles
	protocol = 0;
}

int	bind(int fd, struct sockadrr *addr, int addrlen)
{
	sockaddr_in serverstruc;
	// ? pourquoi ivp4 et pas 6 ?

	serverstruc.sin_family = AF_INET;
	serverstruc.sin_port = // ? comment choisir un port ?
	serverstruc.sin_addr.s_addr = INADDR_ANY; // * any local adress
}

int connect(int fd, struct sockaddr *addr, int addrlen)
{
	// * fd = retour de la fonction socket;
}

int	listen(int fd, int backlog)
{
	// * fd = retour de la fonction socket;
	// * backlog = nbr max co en attente
}
int accept(int fd, struct sockadrr *adrr, int *addrlen)
{
	// ! accept est bloqunt par defaut -> utiliser QU'UN SEUL POOL
	// * fd = retour de la fonction socket;
	// * renvoie un nouveau descripteur de fichier (ou -1 si erreur), c'est sur ce nouveau descripteur qu'on fera nos opérations d'envoi et d'écoute
}

int	recv(int fd, void *buffer, int len, int flags)
{
	// * buffer = points to a buffer where the message should be stored
	// * flags = type of message reception
}

int	send(int fd, char *buffer, int len, int options)
{

}

int shutdown(int fd, int how)
{
	// * how = entier qui contient des drapeaux qui indiquent comment fermer la socket
}

int close(int fd)
{

};

//------------------------------------------------------------------------------------

int	Server::get_fd(void)
{
	return (this->_fd_server);
}

void	Server::set_fd(int fd)
{
	this->_fd_server = fd;
}

int	Server::create_server(std::string arg)
{
	Server	server;
	Client	client;
	int	client_fd;
	struct sockaddr_in sa;
	struct sockaddr_storage client_addr;
	socklen_t addr_size;
	int	bytes_read;
	int	buffer[BUFSIZ];

	memset(&sa, 0, sizeof sa);
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	sa.sin_port = htons(PORT);

	server._fd_server = socket(sa.sin_family, SOCK_STREAM, 0);
	if (server._fd_server == -1)
	{
		throw(std::invalid_argument("invalid socket\n"));
		return (1);
	}
	server._status = bind(server._fd_server, (struct sockaddr*)&sa, sizeof sa);
	if (server._status == -1)
	{
		throw(std::invalid_argument("invalid server status\n"));
		return (1);
	}
	server._status = listen(server._fd_server, 20);
	if (server._status == -1)
	{
		throw(std::invalid_argument("invalid status\n"));
		return (1);
	}
	addr_size = sizeof(client_addr);
	client_fd = accept(server._fd_server, (struct sockaddr *)&client_addr, &addr_size);
	if (client_fd == -1)
	{
		throw(std::invalid_argument("invalid client status\n"));
		return (1);
	}
	client.set_fd(client_fd);
	bytes_read = 1;
	while (bytes_read >= 0)
	{
		bytes_read = recv(client.get_fd(), buffer, BUFSIZ, 0);
		if (bytes_read == -1)
		{
			throw (std::invalid_argument("recv error\n"));
			return (1);
		}
	}
	std::cout << "closing client socket" << std::endl;
	close(client.get_fd());
	std::cout << "closing server socket" << std::endl;
	close(server._fd_server);
	return (0);
}



