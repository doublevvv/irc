#include "../../include/Invite.hpp"

Invite::Invite()
{
	;
}
Invite::Invite(Invite const &obj) : ACommand()
{
	(void)obj;
}

Invite& Invite::operator=(Invite const &obj)
{
	(void)obj;
	return (*this);
}

Invite::~Invite()
{
	;
}

void Invite::execute(Server &server, std::string const &command, std::vector<Client*>::iterator it, std::string const &args)
{
	std::cout << "Entering " << command << " command" << std::endl;
	std::stringstream ss(args);
	std::string word;
	int count = 0;

	while (ss >> word)
	{
		count++;
	}
	if (count < 2)
	{
		server.sendMsgtoClient((*it)->getFd(), ERR_NEEDMOREPARAMS((*it)->getNick()));
		return ;
	}

	ss.clear();
	ss.seekg(0);
	std::string targetNickname;
	std::string channelName;
	ss >> targetNickname >> channelName;
	std::cout << "targetNickname: " << targetNickname << std::endl;
	std::cout << "channelName: " << channelName << std::endl;
	if (!((*it))->tryJoinChannel())
	{
		return ;
	}
	if (targetNickname.size() > 10)
	{
		std::cout << "NICK: max length for targetNickname is 9\n";
		return ;
		// ! return here, must nt go in the setnick function
	}
	for (unsigned int i = 0; i < targetNickname.size(); i++)
	{
		if (targetNickname[1] == ' ' || targetNickname[i] == ' ' || targetNickname[i] == ',' || targetNickname[i] == '*' || targetNickname[i] == '?' ||
			targetNickname[i] == '!' || targetNickname[i] == '@' || targetNickname[i] == '.' || targetNickname[i] == '$' || targetNickname[i] == ':')
		{
			server.sendMsgtoClient((*it)->getFd(), ERR_ERRONEUSNICKNAME((*it)->getNick(), (*it)->getNick()));
			return ;
		}
	}
	// if ((*it)->getUse() == false)
	// {
	// 	(*it)->setNick(nickname); // * pas besoin
	// 	// If used after registration, the server will return a NICK message
	// }

	// if (checkNickname(nickname) == true)
	// {
	// 	nckn.push_back(nickname);
	// 	std::cout << "nickname changed to : " << nickname << std::endl;
	// }
	// if (_used == true)
	// 	std::cout << ERR_NICKNAMEINUSE(nickname, nickname);
	// vector de nickname pou le comparer entre eux et verifier qu'il n'y a aps de doublons
	// 	if (channel.isInvited(user))
	// 	{
	// 		std::cerr << "Error: " << user << " already invited" << std::endl;
	// 		return;
	// 	}
	// 	channel.setInvited(user);
	std::cout << (*it)->getNick() << " invited " << targetNickname << " to " << channelName << std::endl;

	// Verifier si le channel existe
	std::map<std::string, Channel*> &channels = server.getChannels();
	std::map<std::string, Channel*>::iterator ite = channels.find(channelName);

	if (ite == channels.end())
	{
		server.sendMsgtoClient((*it)->getFd(), ERR_NOSUCHCHANNEL((*it)->getNick(), channelName));
		return;
	}
	// Verifier que l’emetteur est operateur du channel
	if ((*it)->getStatus() != OPERATOR)
	{
		server.sendMsgtoClient((*it)->getFd(), ERR_CHANOPRIVISNEEDED((*it)->getNick(), channelName));
		return;
	}
	// Verifier que le client cible existe dans le serveur
	std::vector<Client*> clients = server.getClients();
	Client *targetClient = NULL;

	for (size_t i = 0; i < clients.size(); ++i)
	{
		if (clients[i]->getNick() == targetNickname)
		{
			targetClient = clients[i];
			break;
		}
	}

	if (!targetClient)
	{
		server.sendMsgtoClient((*it)->getFd(), ERR_NOSUCHNICK((*it)->getNick(), targetNickname));
		return;
	}

	// Ajouter le client a la liste des invites du channel
	ite->second->addInvitedClient(targetClient);
	server.sendMsgtoClient(targetClient->getFd(), ":" + (*it)->getNick() + " INVITE " + targetNickname + " to channel " + channelName);
}
