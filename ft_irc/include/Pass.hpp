#ifndef PASS_HPP
# define PASS_HPP

#include "../include/ACommand.hpp"
#include "../include/Client.hpp"
#include "../include/Errors.hpp"
#include "../include/Replies.hpp"

class Client;

class Pass : public ACommand
{
	public:
		Pass();
		Pass(Pass const &obj);
		Pass	&operator=(Pass const &obj);
		virtual ~Pass();

		virtual void execute(std::string const &command, Client &client, const std::string &args);
};

#endif
