#ifndef USER_HPP
# define USER_HPP

#include "../include/ACommand.hpp"
#include "../include/Client.hpp"
#include "../include/Errors.hpp"
#include "../include/Replies.hpp"

class Client;

class User : public ACommand
{
	public:
		User();
		User(User const &obj);
		User	&operator=(User const &obj);
		virtual ~User();

		virtual void execute(std::string const &command, Client &client, const std::string &args);
};

#endif
