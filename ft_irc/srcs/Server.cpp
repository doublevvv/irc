#include "../include/Server.hpp"
#include "../include/Client.hpp"
#include "../include/ACommand.hpp"
#include "../include/AChannel.hpp"
#include "../include/Pass.hpp"
#include "../include/User.hpp"
#include "../include/Nick.hpp"
#include "../include/Kick.hpp"
#include "../include/Channel.hpp"
#include "../include/Errors.hpp"
#include "../include/Replies.hpp"

bool	signalGlobal = 0;

Server::Server() : _fdserver(0), _newfdclient(0), _fdcount(0), idClient()
{

}

Server::~Server()
{
	//* gerer les fermeture de fd
}

void	Server::initServer(Server &server)
{
	(void)server;
	memset(&sa, 0, sizeof(sa));
	// memset((struct sockaddr*) &sa, 0, sizeof(sa));
	int opt = 1;

	_fdserver = socket(AF_INET, SOCK_STREAM, 0);
	if (_fdserver  == -1)
	{
		std::cout << "socket failed : " << strerror(errno) << std::endl;
		return ;
	}
	if (setsockopt(_fdserver, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) < 0)
	{
		std::cout << "error : " << strerror(errno) << std::endl;
		close(_fdserver);
		return ;
	}
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	sa.sin_port = htons(_port);
	if (bind(_fdserver, (struct sockaddr*)&sa, sizeof sa) == -1)
	{
		std::cout << "bind failed : " << strerror(errno) << std::endl;
		close(_fdserver);
		return ;
	}
	if (listen(_fdserver, 20) == -1) //* backlog egal au nombre de fd poll ?
	{
		std::cout << "listen failed : " << strerror(errno) << std::endl;
		close(_fdserver);
		return ;
	}
	std::cout << "Listen on FD SERVER: " << _fdserver<< std::endl;
	memset(&fds, 0, sizeof(fds));
	fds[0].fd = _fdserver;
	fds[0].events = POLLIN;
	_fdcount++;
}


bool Server::checkPoll(Server &server)
{
	std::cout << "POLL FD : " << fds[0].fd << std::endl;
	std::cout << "Waiting on poll()...\n";
	char buffer[1024];
	int	read_bytes;
	while (signalGlobal == 0) // ? boolean ?
	{
		if (poll(fds, _fdcount, -1) <= 0)
		{
			std::cout << "poll failed : " << strerror(errno) << std::endl;
			closeFd();
			return (false);
		}
		if (fds->revents & POLLIN)
		{
			if (fds->fd == _fdserver)
			{
				std::cout << "FDS = " << fds->fd << std::endl;
				newClient();
				std::cout << "Listening socket is readable\n";
			}
		}
		for (std::vector<Client*>::iterator it = idClient.begin(); it != idClient.end(); ++it)
		{
			std::cout << (*it)->getFd() << std::endl;
			std::cout << "RECV here\n";
			memset(buffer, 0, sizeof(buffer));
			read_bytes = recv((*it)->getFd(), buffer, sizeof(buffer), 0); // * 1er arg clientfd
			std::cout<<"read byte == "<<read_bytes<<std::endl;
			buffer[read_bytes] = 0;
			if (read_bytes <= 0)
			{
				if (read_bytes == 0)
					std::cout << "client closed\n"; // QUIt et delete clients
				else
				{
					std::cout << "recv failed : " << strerror(errno) << std::endl;
					closeFd();
				}
				// ? boolean for connection closed = false if error ?
			}
			executeCommands(buffer, server, it);
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

void	Server::closeFd()
{
	for (int i = 0; ;i++)
	{
		close(fds[i].fd);
	}
}

void	Server::newClient()
{
	std::cout << "NEW CLIENT\n";
	struct sockaddr_in client_addr;
	socklen_t addr_size = sizeof(client_addr);

	_newfdclient = accept(_fdserver, (struct sockaddr *)&client_addr, &addr_size);
	// * valeur de retour d'accept est le fd client et l relier au vector du client
	std::cout << "CLIENT FD : " << _newfdclient << std::endl;
	if (_newfdclient < 0)
	{
		if (errno != EWOULDBLOCK)
		{
			std::cout << "accept failed : " << strerror(errno) << std::endl;
			closeFd();
		}
	}
	addClients();
	std::string client_ip = inet_ntoa(client_addr.sin_addr);
	Client *newclient = new Client(_newfdclient);
	idClient.push_back(newclient);
	newclient->setIp(client_ip);
	std::cout << "IP ADD" << newclient->getIp() << std::endl;
	std::cout << "FD COUNT FTER CLIENT" << _fdcount << std::endl;
	// ! Ne pas oublier de close ! ne pas close dans le destructeur
}

int Server::isCommand(const char *str)
{
    int            i;
    int            commandFound;
    const char    *command[] = {"PASS", "USER", "NICK", "PRIVMSG", "CAP", "KICK", "INVITE", "MODE", "TOPIC", NULL};

    i = 0;
    commandFound = -1;
    while (command[i] != NULL)
    {
        if (strcmp(command[i], str) == 0)
        {
            commandFound = i;
            std::cout << "command found: " << commandFound << std::endl;
            break ;
        }
        i++;
    }
    return (commandFound);
}

bool Server::executeCommands(char *buffer, Server &server, std::vector<Client*>::iterator it)
{
	(void)server;
	std::string input(buffer);
	std::stringstream ss(input);
	std::cout << "INPUT: " << input << std::endl;
	std::string commandName;
	std::string args;
	ss >> commandName;
	std::cout << "command: " << commandName << std::endl;
	if (ss.fail())
	{
		std::cerr << "Error: stringstream failed" << std::endl;
		ss.clear();
		return (false);
	}
	int cmdType = isCommand(commandName.c_str());
	if (cmdType == -1)
	{
		std::cerr << "Error: command " << commandName << " does not exist" << std::endl;
		return (false);
	}
	ACommand *userCmd = NULL;
	switch (cmdType)
	{
		case PASS:
			std::cout << "PASS FOUND" << std::endl;
			args = input.substr(5, input.length());
			std::cout << "ARGS: " << args << std::endl;
			userCmd = new Pass();
			userCmd->execute(server,commandName, it, args);
			break ;

		case USER:
			std::cout << "FD USER = " << (*it)->getFd() << std::endl;
			std::cout << "USER FOUND" << std::endl;
			args = input.substr(5, input.length());
			std::cout << "ARGS: " << args << std::endl;
			userCmd = new User();
			userCmd->execute(server, commandName, it, args);
			break ;

		case NICK:
			std::cout << "NICK FOUND" << std::endl;
			args = input.substr(5, input.length());
			std::cout << "ARGS: " << args << std::endl;
			userCmd = new Nick();
			userCmd->execute(server, commandName, it, args);
			break ;

		default:
			std::cerr << "Error: command " << commandName << " does not exist" << std::endl;
			return (false);
	}
	//executeChannelCommands(buffer, client);
	// boolean pour RPL
	return (true);
}


// void	Server::sendMsgtoChannel(Client &client, std::string msg, std::string channel)
// {
// 	std::vector<Client*>::iterator it;
// 	for (it = idClient[channel].begin(); )
// }


void	Server::sendMsgtoClient(int fd, std::string msg)
{
	if (send(fd, msg.data(), msg.size(), 0) < 0)
		std::cout << "send failed : " << strerror(errno) << std::endl;
}
