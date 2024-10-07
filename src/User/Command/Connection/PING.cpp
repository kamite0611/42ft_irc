#include "irc.hpp"

void PING(irc::Command* command)
{
	if (!command->getParameter()[0].length())
		return (command->reply(command->getUser(), 409));
	std::cout << "parameter=" << command->getParameter()[0] << std::endl;
	command->getUser().sendTo(command->getUser(), "PONG " + command->getParameter()[0]);
}