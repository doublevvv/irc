/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doublevv <vv>                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:25:45 by doublevv          #+#    #+#             */
/*   Updated: 2025/08/09 12:01:41 by doublevv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ClientServer.hpp"

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

// int	socket(int domain, int type, int protocol)
// {
// 	domain = AF_INET6;
// 	type = SOCK_STREAM; // *envois successifs d'informations s'additionnent, il n'y a pas de "séparations" entre elles
// 	protocol = 0;
// }

// int	bind(int fd, struct sockadrr *addr, int addrlen)
// {
// 	sockaddr_in serverstruc;
// 	// ? pourquoi ivp4 et pas 6 ?

// 	serverstruc.sin_family = AF_INET;
// 	serverstruc.sin_port = // ? comment choisir un port ?
// 	serverstruc.sin_addr.s_addr = INADDR_ANY; // * any local adress
// }

// int connect(int fd, struct sockaddr *addr, int addrlen)
// {
// 	// * fd = retour de la fonction socket;
// }

// int	listen(int fd, int backlog)
// {
// 	// * fd = retour de la fonction socket;
// 	// * backlog = nbr max co en attente
// }
// int accept(int fd, struct sockadrr *adrr, int *addrlen)
// {
// 	// ! accept est bloqunt par defaut -> utiliser QU'UN SEUL POOL
// 	// * fd = retour de la fonction socket;
// 	// * renvoie un nouveau descripteur de fichier (ou -1 si erreur), c'est sur ce nouveau descripteur qu'on fera nos opérations d'envoi et d'écoute
// }

// int	recv(int fd, void *buffer, int len, int flags)
// {
// 	// * buffer = points to a buffer where the message should be stored
// 	// * flags = type of message reception
// }

// int	send(int fd, char *buffer, int len, int options)
// {

// }

// int shutdown(int fd, int how)
// {
// 	// * how = entier qui contient des drapeaux qui indiquent comment fermer la socket
// }

// int close(int fd)
// {

// };

//------------------------------------------------------------------------------------

int	Server::get_fd(void)
{
	return (this->_fd_server);
}

void	Server::set_fd(int fd)
{
	this->_fd_server = fd;
}

// int	Server::create_server(std::string arg)
// {
// 	Server	server;
// 	Client	client;
// 	int	client_fd;
// 	struct sockaddr_in sa;
// 	struct sockaddr_storage client_addr;
// 	socklen_t addr_size;
// 	int	bytes_read;
// 	int	buffer[BUFSIZ];

// 	memset(&sa, 0, sizeof sa);
// 	sa.sin_family = AF_INET;
// 	sa.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
// 	sa.sin_port = htons(PORT);

// 	server._fd_server = socket(sa.sin_family, SOCK_STREAM, 0);
// 	if (server._fd_server == -1)
// 	{
// 		throw(std::invalid_argument("invalid socket\n"));
// 		return (1);
// 	}
// 	server._status = bind(server._fd_server, (struct sockaddr*)&sa, sizeof sa);
// 	if (server._status == -1)
// 	{
// 		throw(std::invalid_argument("invalid server status\n"));
// 		return (1);
// 	}
// 	server._status = listen(server._fd_server, 20);
// 	if (server._status == -1)
// 	{
// 		throw(std::invalid_argument("invalid status\n"));
// 		return (1);
// 	}
// 	addr_size = sizeof(client_addr);
// 	client_fd = accept(server._fd_server, (struct sockaddr *)&client_addr, &addr_size);
// 	if (client_fd == -1)
// 	{
// 		throw(std::invalid_argument("invalid client status\n"));
// 		return (1);
// 	}
// 	client.set_fd(client_fd);
// 	bytes_read = 1;
// 	while (bytes_read >= 0)
// 	{
// 		bytes_read = recv(client.get_fd(), buffer, BUFSIZ, 0);
// 		if (bytes_read == -1)
// 		{
// 			throw (std::invalid_argument("recv error\n"));
// 			return (1);
// 		}
// 	}
// 	std::cout << "closing client socket" << std::endl;
// 	close(client.get_fd());
// 	std::cout << "closing server socket" << std::endl;
// 	close(server._fd_server);
// 	return (0);
// }

/*
SETSOCKOPT is short for "set socket option", which pretty well sums up what its purpose is -- as a generic way to set various options for a socket. It's designed to be flexible enough to
support both current optional-functionality as well as any additional options that might be added to the network stack in the future, hence the (rather awkward) pass-by-pointer-and-size
semantics of the call, which can be used to pass any type or amount of option-configuring data if necessary.
As to the particular options specified (incorrectly, btw) in your code snippet: the SO_REUSEADDR arg tells the OS that calls to bind() this socket are allowed to reuse a
local address; this is particularly useful when stopping and then quickly restarting a server, since otherwise the address you want to bind to might still be allocated to the
previous server instance, and thus your server won't be able to bind() to it for several minutes.
SO_REUSEPORT tells the OS that you'd like to allow multiple sockets to bind to the same socket address simultaneously; it's useful e.g.
when running multiple clients that all want to receive the multicast or broadcast traffic coming in on a given port simultaneously.
*/

int	Server::init_server()
{
	Server	serv;
	struct sockaddr_in sa;

	memset(&sa, 0, sizeof sa);

	serv._fd_server = socket(AF_INET, SOCK_STREAM, 0);
	if (serv._fd_server < -1)
	{
		std::cout << "socket failed : " << strerror(errno) << std::endl;
		return (1);
	}
	std::cout << "SERVER FD : " << _fd_server << std::endl;
	const int opt = 1;
	if (setsockopt(serv._fd_server, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) < 0)
	{
		std::cout << "error : " << strerror(errno) << std::endl;
		return (1);
	}
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	sa.sin_port = htons(PORT);
	memset((struct sockaddr*) &sa, 0, sizeof(sa));
	serv._status = bind(serv._fd_server, (struct sockaddr*)&sa, sizeof sa);
	if (serv._status == -1)
	{
		std::cout << "SERVER FD INSIDE : " << _fd_server << std::endl;
		std::cout << "bind failed : " << strerror(errno) << std::endl;
		return (1);
	}
	std::cout << "SERVER STATUS : " << _status << std::endl;
	std::cout << "here\n";
	serv._status = listen(serv._fd_server, 20);
	std::cout << "LISTEN STATUS : " << _status << std::endl;
	if (serv._status == -1)
	{
		std::cout << "listen failed : " << strerror(errno) << std::endl;
		return (1);
	}
	return (0);
}

int	Server::checkPoll()
{
	Server	serv;
	struct pollfd fds[FD_COUNT];
	// nfds_t	nfds;

	memset(fds, 0, sizeof(fds));
	fds[0].fd = _fd_server;
	fds[0].events = POLLIN;
	// ? timeout ?
	int timeout = (1 * 60 * 1000);
	std::cout << "Waiting on poll()...\n";
	serv._status = poll(fds, 5, timeout);
	if (serv._status < 0)
	{
		std::cout << "poll failed : " << strerror(errno) << std::endl;
		// ! ne pas oublier de fermer les fd a chaque erreur (fonction pour gerer ca)
		return (1);
	}
	// ? verifier le timeout ?
	if (serv._status == 0)
	{
		std::cout << "timeout\n";
		return(1);
	}
	int size = 5;
	for (int i = 0; i < size; i++)
	{
		if (fds[i].revents == 0)
		{

			std::cout<< "here\n";
			continue ;
		}
		if (fds[i].fd == serv._fd_server)
		{
			//* accepter nouveaux clients
			serv.newClient();
			std::cout << "Listening socket is readable\n";
		}
		else
			serv.newData();
		// * receives new data
	}
	return (0);
}

int	Server::newClient()
{
	Server serv;
	struct sockaddr_in sa_client;
	struct pollfd fds[FD_COUNT];

	memset(&sa_client, 0, sizeof sa_client);

	serv._newclientfd = accept(serv._fd_server, NULL, NULL);
	// * valeur de retour d'accept est le fd client et l relier au vector du client
	if (serv._newclientfd < 0)
	{
		if (errno != EWOULDBLOCK)
			std::cout << "accept failed : " << strerror(errno) << std::endl;
		return (1); // ? ou break ?
	}
	std::cout << "New incoming connection - %d\n" << serv._newclientfd;
	fds[5].fd = serv._fd_server;
	fds[5].events = POLLIN;
	return (0);
}

int	Server::newData()
{
	Server serv;
	Client cli;
	int	len;
	int	buffer[BUFSIZ];
	struct pollfd fds[FD_COUNT];

	for (int i = 0; i < FD_COUNT; i++)
	{
		serv._data_client = recv(fds[i].fd, buffer, sizeof(buffer), 0);
		if (serv._data_client < 0)
		{
			if (errno != EWOULDBLOCK)
				std::cout << "recv failed : " << strerror(errno) << std::endl;
		}
		break ;
		if (serv._data_client == 0)
		{
			std::cout << "connection closed\n";
			break ;
		}
		len = serv._data_client;
		std::cout << "%d bytes received\n" << len;
		serv._data_client = send(fds[i].fd, buffer, len, 0);
		if (serv._data_client < 0)
		{
			std::cout << "connection closed\n";
						break ;
		}
		cli.initClient();

	}
	// ! ne pas oublier de close tous les fd
}

