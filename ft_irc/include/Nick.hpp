#ifndef NICK_HPP
# define NICK_HPP

#include "../include/ACommand.hpp"
#include "../include/Client.hpp"
#include "../include/Errors.hpp"
#include "../include/Replies.hpp"

class Client;

class Nick : public ACommand
{
	public:
		Nick();
		Nick(Nick const &obj);
		Nick	&operator=(Nick const &obj);
		virtual ~Nick();

		virtual void execute(std::string const &command, Client &client, const std::string &args);
};

#endif
