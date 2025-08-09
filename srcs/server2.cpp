#include "../include/Server.hpp"

Server::Server() : _fdserver(0), _newfdclient(0), _fdcount(0)
{
	if (!initServer())
	{
		std::cout << "error constructeur\n";
		return ;
	}
}

Server::~Server()
{
	//* gerer les fermeture de fd
}

bool	Server::initServer()
{
	memset(&sa, 0, sizeof(sa));
	int opt = 1;

	_fdserver = socket(AF_INET, SOCK_STREAM, 0);
	if (_fdserver  == -1)
	{
		std::cout << "socket failed : " << strerror(errno) << std::endl;
		return (false);
	}
	if (setsockopt(_fdserver, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) < 0)
	{
		std::cout << "error : " << strerror(errno) << std::endl;
		return (false);
	}
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	sa.sin_port = htons(PORT);
	memset((struct sockaddr*) &sa, 0, sizeof(sa));
	if (bind(_fdserver, (struct sockaddr*)&sa, sizeof sa) == -1)
	{
		std::cout << "bind failed : " << strerror(errno) << std::endl;
		return (false);
	}
	if (listen(_fdserver, 20) == -1) //* backlog egal au nombre de fd poll ?
	{
		std::cout << "listen failed : " << strerror(errno) << std::endl;
		return (false);
	}
	std::cout << "SERVER FD : " << _fdserver << std::endl;
	_fdcount++;
	return (true);
}

bool	Server::checkPoll()
{
	memset(fds, 0, sizeof(fds));
	fds[0].fd = _fdserver;
	fds[0].events = POLLIN;
	std::cout << "POLL FD : " << fds[0].fd << std::endl;
	std::cout << "FD COUNT : " << _fdcount << std::endl;
	std::cout << "Waiting on poll()...\n";
	if (poll(fds, _fdcount, (1 * 60 * 1000)) < 0)
	{
		std::cout << "poll failed : " << strerror(errno) << std::endl;
		return (false);
	}
	if (poll(fds, _fdcount, (1 * 60 * 1000)) == 0)
	{
		std::cout << "timeout\n";
		return (false);
	}
	for (int i = 0; i < _fdcount; i++)
	{
		std::cout << "here\n";
		if (fds[i].revents || POLLIN)
		{
			if (fds[i].fd == _fdserver)
			{
				//* accepter nouveaux clients
				std::cout << "Listening socket is readable\n";
				if (!newClient())
					return (false);
			}
			else
				newData();
			// * receives new data
		}
	}
	return (true);
}
bool	Server::newClient()
{
	std::cout << "NEW CLIENT\n";
	struct sockaddr_in sa_client;
	struct sockaddr_storage client_addr;
	socklen_t addr_size = sizeof(client_addr);

	_newfdclient = accept(_fdserver, (struct sockaddr *)&client_addr, &addr_size);
	// * valeur de retour d'accept est le fd client et l relier au vector du client
	std::cout << "CLIENT FD : " << _fdserver << std::endl;
	if (_newfdclient < 0)
	{
		if (errno != EWOULDBLOCK)
			std::cout << "accept failed : " << strerror(errno) << std::endl;
		return (false);
	}
	std::cout << "New incoming connection - %d\n" << _newfdclient;
	fds[_fdcount].fd = _fdserver;
	fds[_fdcount].events = POLLIN;
	
	return (true);
}

bool	Server::newData()
{

}
