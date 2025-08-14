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

// void	Server::add_epoll(int epoll_fd, int fd, int events)
// {
// 	struct epoll_event poll_event;

// 	memset(&events, 0, sizeof(struct epoll_event));
// 	poll_event.events = events;
// 	poll_event.data.fd = fd;
// 	std::cout << "POLL FD : " << epoll_fd << "\n";
// 	if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &poll_event) < 0)
// 	{
// 		std::cout << "epoll add failed : " << strerror(errno) << std::endl;
// 		return ;
// 	}
// 	return ;
// }

bool	Server::initServer()
{
	memset(&sa, 0, sizeof(sa));
	memset((struct sockaddr*) &sa, 0, sizeof(sa));
	int opt = 1;

	// _epollfd = epoll_create(255);
	// if (_epollfd < 0)
	// {
	// 	std::cout << "epoll create failed : " << strerror(errno) << std::endl;
	// 	return (false);
	// }
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
	std::cout << "Listen on FD SERVER: " << _fdserver<< std::endl;
	// add_epoll(_epollfd, _fdserver, EPOLLIN);
	fds[0].fd = _fdserver;
	fds[0].events = POLLIN;
	_fdcount++;
	return (true);
}

bool	Server::checkPoll()
{
	// memset(fds, 0, sizeof(fds));
	// struct epoll_event events[_fdcount];
	std::cout << "POLL FD : " << fds[0].fd << std::endl;
	std::cout << "Waiting on poll()...\n";
	while (1) // ? boolean ?
	{
		if (poll(fds, _fdcount, -1) <= 0)
		{
			// _fdcount++;
			std::cout << "poll failed : " << strerror(errno) << std::endl;
			return (false);
		}
		for (int i = 0; i < _fdcount; i++)
		{
			if (fds[i].revents && POLLIN)
			{
				if (fds[i].fd == _fdserver)
				{
					//* accepter nouveaux clients
					std::cout << "FDS[I] = " << _fdcount << std::endl;
					 std::cout << "i = " << i << std::endl;
					 newClient();
					//  std::cout << "Listening socket is readable\n";
				}
				else
				{
					// std::cout << "here\n";
					newData(i);
				}
			}
		}
	}
	return (true);
}

void	Server::addClients()
{
	for (int k = 0; ;k++)
	{
		if (fds[k].fd == 0)
		{
			std::cout << "K : " << fds[k].fd << std::endl;
			// ! le remettre a zero car si rempli, boucle infini //removeClient(fd) addClient(fd)
			fds[k].fd = _newfdclient;
			fds[k].events = POLLIN | POLLOUT;
			_fdcount++;
			break;
		}
	}
}

void	Server::deleteClients(int index)
{
	fds[index] = fds[_fdcount - 1];
	std::cout << "DELETE FDS : " << fds[index].fd << std::endl;
	_fdcount--;
	std::cout << "FD COUNT-- " << _fdcount << std::endl;
}

void	Server::newClient()
{
	std::cout << "NEW CLIENT\n";
	// struct sockaddr_in sa_client;
	struct sockaddr_storage client_addr;
	socklen_t addr_size = sizeof(client_addr);

	_newfdclient = accept(_fdserver, (struct sockaddr *)&client_addr, &addr_size);
	// * valeur de retour d'accept est le fd client et l relier au vector du client
	std::cout << "CLIENT FD : " << _newfdclient << std::endl;
	if (_newfdclient < 0)
	{
		if (errno != EWOULDBLOCK)
			std::cout << "accept failed : " << strerror(errno) << std::endl;
		// return (false);
	}
	// std::cout << "New incoming connection = " << _newfdclient;
	// fds[_fdcount].fd = _fdserver;
	// fds[_fdcount].events = POLLIN;
	addClients();
	// pollfd newClientPollFd;
	// newClientPollFd.fd = _newfdclient;
	// newClientPollFd.events = POLLIN | POLLOUT;
	// clienfds.push_back(newClientPollFd);
	std::cout << "FD COUNT FTER CLIENT" << _fdcount << std::endl;
	// ! Ne pas oublier de close ! ne pas close dans le destructeur
	// return (true);
}

bool	Server::newData(int index)
{
	char buffer[1024];
	int	read_bytes;

	std::cout << "RECV here\n";
	read_bytes = recv(fds[index].fd, buffer, sizeof(buffer), 0); // * 1er arg clientfd
	std::cout<<"read byte == "<<read_bytes<<std::endl;
	buffer[read_bytes] = 0;
	std::cout<<"**********************************************************************************"<<std::endl;
	printf("%s\n", buffer);
	std::cout<<"**********************************************************************************"<<std::endl;
	if (read_bytes <= 0)
	{
		if (read_bytes == 0)
		std::cout << "client closed\n";
		else
		std::cout << "recv failed : " << strerror(errno) << std::endl;
		// ? boolean for connection closed = false if error ?
	}
	_fdcount++;
	deleteClients(index);
	// else
		//* execute commands
	return (true);
}

/*
* GERER COMMANDES : You must be able to authenticate, set a nickname, a username, join a channel,
* send and receive private messages using your reference client
*/
