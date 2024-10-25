#include "irc.hpp"

void PING(irc::Command* command)
{
	if (command->getParameter().size() == 0)
		return (command->reply(command->getUser(), 409));
	command->getUser().sendTo(command->getUser(), "PONG " + command->getParameter()[0]);
}