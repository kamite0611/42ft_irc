#include "irc.hpp"

void USER(irc::Command* command)
{
	if (command->getParameter().size() < 3)
		return (command->reply(command->getUser(), 461));
	if (command->getUser().getStatus() != irc::REGISTER)
		return (command->reply(command->getUser(), 462));

	command->getUser().setSserName(command->getPrefix());
	command->getUser().setRealname(command->getTraile)
}

/*
USER <username> <hostname> <servername> :<realname>
*/