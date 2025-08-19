#include "../include/Server.hpp"
#include "../include/Client.hpp"
#include "../include/Channel.hpp"
#include "../include/AChannelCommand.hpp"
// #include "../include/UserCommand.hpp"
#include "../include/Errors.hpp"
#include "../include/Replies.hpp"

bool	signalGlobal = 0;

Server::Server() : _fdserver(0), _newfdclient(0), _fdcount(0)
{

}

Server::~Server()
{
	//* gerer les fermeture de fd
}

void	Server::initServer()
{
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

bool	Server::checkPoll()
{
	std::cout << "POLL FD : " << fds[0].fd << std::endl;
	std::cout << "Waiting on poll()...\n";
	while (signalGlobal == 0) // ? boolean ?
	{
		if (poll(fds, _fdcount, -1) <= 0)
		{
			std::cout << "poll failed : " << strerror(errno) << std::endl;
			closeFd();
			return (false);
		}
		for (int i = 0; i < _fdcount; i++)
		{
			std::cout<<"mask? "<<fds[i].revents << " i == "<<i<<" revents == "<<fds[i].revents <<" pollin == " <<POLLIN<<std::endl;
			if (fds[i].revents | POLLIN)
			{
				if (fds[i].fd == _fdserver)
				{
					//* accepter nouveaux clients
					std::cout << "FDS[I] = " << _fdcount << std::endl;
					 std::cout << "i = " << i << std::endl;
					 newClient();
					 std::cout << "Listening socket is readable\n";
				}
				else
					newData(i);
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

bool	Server::newData(int index)
{
	char buffer[1024];
	int	read_bytes;

	std::cout << "RECV here\n";
	read_bytes = recv(fds[index].fd, buffer, sizeof(buffer), 0); // * 1er arg clientfd
	std::cout<<"read byte == "<<read_bytes<<std::endl;
	buffer[read_bytes] = 0;
	// std::cout<<"**********************************************************************************"<<std::endl;
	// std::cout<<"buffer = " << buffer<<std::endl;
	// std::cout<<"**********************************************************************************"<<std::endl;
	if (read_bytes <= 0)
	{
		if (read_bytes == 0)
			std::cout << "client closed\n";
		else
		{
			std::cout << "recv failed : " << strerror(errno) << std::endl;
			closeFd();
		}
		// ? boolean for connection closed = false if error ?
	}
	// else
	// {
	// 	std::cout << "" << fds[index].fd << " got message : " << buffer << std::endl;
	// 	std::cout << "LEN = " << sizeof(read_bytes) << std::endl;
	// 	int rc = send(fds[index].fd, buffer, read_bytes, 0);
	// 	if (rc < 0)
	// 	{
	// 		std::cout << "send failed : " << strerror(errno) << std::endl;
	// 	}
	// }
	// ! ne pas toucher commentaire au desssus
	else
	{
		// EXECUTE COMMANDS
		if (!executeCommands(buffer))
		{
			return (false);
		}
	}
	deleteClients(index);
	_fdcount++;
	return (true);
}

bool Server::executeCommands(char *buffer)
{
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

	Channel *channel = NULL;
	int cmdType = channel->isChannelCommand(commandName.c_str());
	if (cmdType == -1)
	{
		std::cerr << "Error: command " << commandName << " does not exist" << std::endl;
		return (false);
	}

	Client client;
	// AChannelCommand *cmd = NULL;
	switch (cmdType)
	{
		case USER:
			args = input.substr(5, input.length());
			std::cout << "ARGS: " << args << std::endl;
			if (args.empty())
			{
				std::cerr << "Error: Missing arguments" << std::endl;
				std::cout << ERR_NEEDMOREPARAMS(NULL) << std::endl;
				return (false);
			}
			client.execute(commandName, args);
			break ;

		case PASS:
			std::cout << "PASS FOUND" << std::endl;
			args = input.substr(5, input.length());
			std::cout << "ARGS: " << args << std::endl;
			if (args.empty())
			{
				std::cerr << "Error: Missing arguments" << std::endl;
				std::cout << ERR_NEEDMOREPARAMS(NULL) << std::endl;
				return (false);
			}
			client.executePWD(commandName, args);
			break ;

		case NICK:
			std::cout << "NICK FOUND" << std::endl;
			args = input.substr(5, input.length());
			std::cout << "ARGS: " << args << std::endl;
			if (args.empty())
			{
				std::cerr << "Error: Missing arguments" << std::endl;
				std::cout << ERR_NONICKNAMEGIVEN;
				return (false);
			}
			client.executeNick(commandName, args);
			break ;
		// case KICK:
		// 	if (args.empty())
		// 	{
		// 		std::cerr << "Error: Missing arguments" << std::endl;
		// 		//std::cout << ERR_NEEDMOREPARAMS(nickname, command) << std::endl;
		// 		//return (false);
		// 	}
		// 	args = input.substr(5, input.length());
		// 	std::cout << "args: " << args << std::endl;
		// 	//cmd = new KickCommand();
		// 	cmd->execute(commandName, args);
		// 	break ;
		// 	case INVITE:
		// 		if (args.empty())
		// 		{
		// 			std::cerr << "Error: Missing arguments" << std::endl;
		// 			// std::cout << ERR_NEEDMOREPARAMS(nickname, command) << std::endl;
		// 			return (false);
		// 		}
		// 		args = input.substr(7, input.length());
		// 		std::cout << "args: " << args << std::endl;
		// 		cmd = new InviteCommand();
		// 		cmd->execute(commandName, args);
		// 		break ;
		// 	case TOPIC:
		// 		if (args.empty())
		// 		{
		// 			std::cerr << "Error: Missing arguments" << std::endl;
		// 			// std::cout << ERR_NEEDMOREPARAMS(nickname, command) << std::endl;
		// 			return (false);
		// 		}
		// 		args = input.substr(6, input.length());
		// 		std::cout << "args: " << args << std::endl;
		// 		cmd = new TopicCommand();
		// 		cmd->execute(commandName, args);
		// 		break ;
		// 	case MODE:
		// 		if (args.empty())
		// 		{
		// 			std::cerr << "Error: Missing arguments" << std::endl;
		// 			// std::cout << ERR_NEEDMOREPARAMS(nickname, command) << std::endl;
		// 			return (false);
		// 		}
		// 		args = input.substr(5, input.length());
		// 		std::cout << "args: " << args << std::endl;
		// 		cmd = new ModeCommand();
		// 		cmd->execute(commandName, args);
		// 		break ;
		// 	default:
		// 		std::cerr << "Error: command " << commandName << " does not exist" << std::endl;
		// 		//return (false);
	}
	return (true);
}
/*
* GERER COMMANDES : You must be able to authenticate, set a nickname, a username, join a channel,
* send and receive private messages using your reference client
*/

// void	Server::closeFds(void)
// {
// 	std::cout << "All fds are closed" << std::endl;
// 	close(this->_socketFd);
// }

// void	Server::initServer(void)
// {
// 	while (!signalGlobal)
// 	{
// 		...
// 	}
// 	closeFds();
// }

// void	Server::sendMsgtoClient(Client &client, std::string msg)
// {
// 	if (send(client.getFd(), msg.data(), msg.size(), 0) < 0)
// 		std::cout << "send failed : " << strerror(errno) << std::endl;
// }

// void	Server::sendMsgtoChannel(Client &client, std::string msg, std::string channel)
// {
// 	std::vector<Client*>::iterator it;


// ! ne pas oublier de rediriger les messages d'erreurs au client correspondant
