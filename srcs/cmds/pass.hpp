#ifndef Pass_HPP
#define Pass_HPP

#include <string>
#include <iostream>
#include <sstream>

class PassCommand
{
	public:
	PassCommand();
	~PassCommand();
	void	execute(std::string const &command, std::string const &args);
	void	executeCmd(std::string const &command,std::string);

	private:
};

#endif
