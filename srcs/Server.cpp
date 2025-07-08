/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doublevv <vv>                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:25:45 by doublevv          #+#    #+#             */
/*   Updated: 2025/07/08 07:56:12 by doublevv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientServer.hpp"

/*
		SERVER:
	1) creation d'une socket, retourne un numero de descripteur "SOCKET"
	2) associer une socket, specifier type de communication associe au socket (TCP) "BIND"
	3) ecouter un port, pls connexions sur un meme port "LISTEN"
	4) accepter un connexion "ACCEPT"
	> bloque un attendnat co client
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

}




