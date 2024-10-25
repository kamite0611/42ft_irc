#include "irc.hpp"

void PONG(irc::Command* command)
{
	if (command->getParameter().size() == 0)
		return (command->reply(command->getUser(), 409));
	command->getUser().setLastPingTime(std::time(0));
}