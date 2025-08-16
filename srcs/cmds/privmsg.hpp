#ifndef Privmsg_HPP
#define Privmsg_HPP

#include <string>
#include <iostream>
#include <sstream>

class PrivmsgCommand
{
	public:
	PrivmsgCommand();
	~PrivmsgCommand();
	void	execute(std::string const &command, std::string const &args);
	void	executeCmd(std::string, std::string);

	private:
};

#endif
