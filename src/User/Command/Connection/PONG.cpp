#include "irc.hpp"

void PONG(irc::Command* command)
{
	std::cout << "*********" << command->getParameter()[0] << std::endl;
	if (!command->getParameter()[0].length())
		return (command->reply(command->getUser(), 409));
	if (command->getParameter()[0] != command->getServer().getConfig().get("name"))
		return (command->reply(command->getUser(), 402, command->getParameter()[0]));
	command->getUser().setLastPingTime(std::time(0));
}