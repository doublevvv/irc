#ifndef Nick_HPP
#define Nick_HPP

#include <string>
#include <iostream>
#include <sstream>

class NickCommand
{
	public:
	NickCommand();
	~NickCommand();
	void	execute(std::string const &command, std::string const &args);
	void	executeCmd(std::string);

	private:
	bool _used;
};

#endif
