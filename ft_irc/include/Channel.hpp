#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include "Client.hpp"
#include <iostream>
#include <map>
#include <vector>

enum e_channelRole
{
	OPERATOR,
	MEMBER
};

// enum e_channelCommands {
// 	KICK, // Eject a client from the channel
// 	INVITE, // Invite a client to a channel
// 	MODE, // Change the channel's mode
// 	TOPIC // Change or view the channel topic
// };

class Client;

class Channel
{
	public:
		Channel();
		Channel(std::string const &name);
		Channel(Channel const &obj);
		Channel	&operator=(Channel const &obj);
		~Channel();

		std::string const &getName(void) const;
		std::string const &getPassword(void) const;
		std::string	const &getTopic(void) const;
		std::vector<Client*> const &getClientlist(void) const;
		bool getTopicRestrictions(void) const;
		bool getInvited(void) const;
		int getLimit(void) const;
		int getNbUsers(void) const;

		void setName(std::string const &name);
		void setPassword(std::string const &password);
		bool setTopic(std::string const &topic, std::string const &username);
		void setInvited(std::string const &client);

		int isChannelCommand(const char *str);
		void checkParameterChannel(std::string const &channelName);
		bool isValid(std::string const &str);
		void addChannel(Channel &channel);
		bool isInvited(std::string const &client);
		bool isClientInChannel(std::string const &name);
		void addClient(Client *client);
		void removeClient(std::string const &name);
		std::string getClient(std::string const &username) const;
		std::vector<std::string> getClients(void) const;
		Channel &getChannelByName(std::string const &name);

		// Modes
		bool modeI(std::string const &client, std::string const &arg);
		bool modeK(std::string const &client, std::string const &arg, std::string const &password);
		bool modeL(std::string const &client, std::string const &arg, int const &limit);
		bool modeO(std::string const &client, std::string const &arg, std::string const &target);
		bool modeT(std::string const &client, std::string const &arg);

	private:
		std::string	_name;
		std::string	_password;
		std::string	_topic;
		bool	_topicRestrictions;
		bool	_isInvited;
		int	_userLimit;

		std::vector<Client*>	_clients;
		std::vector<std::string>	_invited;
		std::map<std::string, Channel*> _channels;
};

#endif
