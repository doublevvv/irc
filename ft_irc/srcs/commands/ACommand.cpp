#include "../../include/ACommand.hpp"

ACommand::ACommand()
{
	;
}

ACommand::ACommand(ACommand const &obj)
{
	(void)obj;
}

ACommand& ACommand::operator=(ACommand const &obj)
{
	(void)obj;
	return (*this);
}

ACommand::~ACommand()
{
	;
}
