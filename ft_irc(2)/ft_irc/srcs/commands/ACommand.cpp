// #include "../../include/ACommand.hpp"

// std::set<int> ACommand::retrieveClient(Server &server, Channel &channel, std::string nickname)
// {
// 	std::cout << "CHANNEL WHAT INSIDE = " << &channel << std::endl;
// 	std::map<std::string, int> clients = channel.getClientList();
// 	std::set<int> fds;
// 	std::map<std::string, int>::iterator it;

// 	for (it = clients.begin(); it != clients.end(); it++)
// 	{
// 		int fd = server.getClientFd(nickname);
// 		if (fd != -1)
// 		{
// 			fds.insert(fd);
// 		}
// 	}
// 	return (fds);
// }
