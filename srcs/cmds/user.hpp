#ifndef USER_HPP
#define USER_HPP

#include <string>
#include <iostream>
#include <sstream>

class UserCommand
{
	public:
	UserCommand();
	~UserCommand();
	bool	UserCommand::getUse();
	void	execute(std::string const &command, std::string const &args);
	void	executeCmd(std::string const &command, std::string, int, char, std::string);

	private:
	bool	_used;
};

#endif
