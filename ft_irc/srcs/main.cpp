#include "../include/Server.hpp"

int	main(int argc, char *argv[])
{
	if (argc != 3)
	{
		std::cerr << "Usage: ./ircserv <port> <password>" << std::endl;
		return (1);
	}
	else
	{
		Server	server;
		std::cout << "----- Server -----" << std::endl;

		try
		{
			server.setSignal();
			server.checkArgs(argv);
			server.initServer();
			server.checkPoll();
		}
		catch(const std::exception& e)
		{
			//server.closeFds();
			std::cerr << e.what() << std::endl;
		}
		std::cout << "The server is closed" << std::endl;

	// 	std::string input;
	// 	std::getline(std::cin, input);
	// 	std::cout << "input = " << input << std::endl;
	// 	std::stringstream ss(input);
	// 	std::string commandName;
	// 	std::string args;
	// 	ss >> commandName;
	// 	if (ss.fail())
	// 	{
	// 		std::cerr << "Error: stringstream failed" << std::endl;
	// 		ss.clear();
	// 	}
	// 	std::cout << "command: " << commandName << std::endl;
	// 	int cmdType = isChannelCommand(commandName.c_str());
	// 	if (cmdType == -1)
	// 	{
	// 		std::cerr << "Error: command " << commandName << " does not exist" << std::endl;
	// 		return (1);
	// 	}
	// 	AChannelCommand *cmd = NULL;
	// 	switch (cmdType)
	// 	{
	// 		case KICK:
	// 			if (args.empty())
	// 			{
	// 				std::cerr << "Error: Missing arguments" << std::endl;
	// 				// std::cout << ERR_NEEDMOREPARAMS(nickname, command) << std::endl;
	// 				return (1);
	// 			}
	// 			args = input.substr(5, input.length());
	// 			std::cout << "args: " << args << std::endl;
	// 			cmd = new KickCommand();
	// 			break ;
	// 		case INVITE:
	// 			if (args.empty())
	// 			{
	// 				std::cerr << "Error: Missing arguments" << std::endl;
	// 				// std::cout << ERR_NEEDMOREPARAMS(nickname, command) << std::endl;
	// 				return (1);
	// 			}
	// 			args = input.substr(7, input.length());
	// 			std::cout << "args: " << args << std::endl;
	// 			cmd = new InviteCommand();
	// 			break ;
	// 		case TOPIC:
	// 			if (args.empty())
	// 			{
	// 				std::cerr << "Error: Missing arguments" << std::endl;
	// 				// std::cout << ERR_NEEDMOREPARAMS(nickname, command) << std::endl;
	// 				return (1);
	// 			}
	// 			args = input.substr(6, input.length());
	// 			std::cout << "args: " << args << std::endl;
	// 			cmd = new TopicCommand();
	// 			break ;
	// 		case MODE:
	// 			if (args.empty())
	// 			{
	// 				std::cerr << "Error: Missing arguments" << std::endl;
	// 				// std::cout << ERR_NEEDMOREPARAMS(nickname, command) << std::endl;
	// 				return (1);
	// 			}
	// 			args = input.substr(5, input.length());
	// 			std::cout << "args: " << args << std::endl;
	// 			cmd = new ModeCommand();
	// 			break ;
	// 		default:
	// 			std::cerr << "Error: command " << commandName << " does not exist" << std::endl;
	// 			return (1);
	// 	}
	// 	cmd->execute(commandName, args);
	// 	delete cmd; // => Free allocation
	}
	return (0);
}
