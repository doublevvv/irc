// #include "../../include/ModeCommand.hpp"

// ModeCommand::ModeCommand()
// {
// 	;
// }

// ModeCommand::ModeCommand(ModeCommand const &obj)
// {
// 	(void)obj;
// }

// ModeCommand& ModeCommand::operator=(ModeCommand const &obj)
// {
// 	(void)obj;
// 	return (*this);
// }

// ModeCommand::~ModeCommand()
// {
// 	;
// }

// void ModeCommand::execute(std::string const &command, std::string const &args)
// {
// 	std::cout << "Entering " << command << " command" << std::endl;

// 	std::stringstream ss(args);
// 	std::string channelName;
// 	ss >> channelName;
// 	std::cout << "channelName: " << channelName << std::endl;

// 	std::string arg;
// 	arg = args.substr(channelName.length() + 1, args.length());
// 	std::cout << "arg: " << arg << std::endl;

// 	Channel chan;
// 	Channel& channel = chan.getChannelByName(channelName);
// 	// le user est celui qui est a l'origine de la requete
// 	executeCmd(channel, "", arg);
// }

// void ModeCommand::executeCmd(Channel& channel, std::string const &user, std::string const &args)
// {
// 	(void)channel;
// 	(void)user;
// 	std::cout << "args: " << args << std::endl;
// 	std::string modeFlag;
// 	modeFlag = args.substr(0, 2);
// 	std::cout << "modeFlag: " << modeFlag << std::endl;

// 	if (modeFlag.empty())
// 	{
// 		std::cerr << "Error: no mode specified" << std::endl;
// 		return;
// 	}
// 	else if (modeFlag == "+i" || modeFlag == "-i") // Set/remove Invite-only channel
// 	{
// 		if (channel.modeI(user(CLIENT), modeFlag))
// 		{
// 			std::cout << "Invite mode set to " << modeFlag << std::endl;
// 		}
// 		else
// 		{
// 			std::cerr << "Error: " << user(CLIENT) << " cannot change invite mode" << std::endl;
// 		}
// 	}
// 	else if (modeFlag == "+k" || modeFlag == "-k") // Set/remove the channel key (password)
// 	{
// 		if (channel.modeK(user(CLIENT), modeFlag, NEW_PASSWORD))
// 		{
// 			std::cout << "Channel key has been changed" << std::endl;
// 		}
// 		else
// 		{
// 			std::cerr << "Error: " << user(CLIENT) << " cannot change channel key" << std::endl;
// 		}
// 	}
// 	else if (modeFlag == "+l" || modeFlag == "-l") // Set/remove the user limit to channel
// 	{
// 		std::string userLimit;
// 		userLimit = args.substr(modeFlag.length(), args.length());
// 		std::cout << "userLimit: " << userLimit << std::endl;
// 		if (channel.modeL(user(CLIENT), modeFlag, userLimit))
// 		{
// 			std::cout << "User " << user << "limited the channel to " << userLimit << " user(s)" << std::endl;
// 		}
// 		else
// 		{
// 			std::cerr << "Error: " << user << " cannot change user limit" << std::endl;
// 		}
// 	}
// 	else if (modeFlag == "+o" || modeFlag == "-o") // Give/take channel operator privilege
// 	{
// 		std::string target;
// 		target = args.substr(modeFlag.length(), args.length());
// 		if (channel.modeO(user(CLIENT), modeFlag, target))
// 		{
// 			std::cout << "User " << user(CLIENT) << "granted " << target << " the operator role " << std::endl;
// 		}
// 		else
// 		{
// 			std::cerr << "Error: " << user << " cannot change channel operator privilege" << std::endl;
// 		}
// 	}
// 	else if (modeFlag == "+t" || modeFlag == "-t") // Set/remove the restrictions of the TOPIC command to channel operators
// 	{
// 		if (channel.modeT(user(CLIENT), modeFlag))
// 		{
// 			std::cout << "User " << user(CLIENT) << "changed topic restrictions " << std::endl;
// 		}
// 		else
// 		{
// 			std::cerr << "Error: " << user << " cannot change topic restriction" << std::endl;
// 		}
// 	}
// 	else
// 	{
// 		std::cerr << "Unknown mode: " << modeFlag << std::endl;
// 	}
// }
