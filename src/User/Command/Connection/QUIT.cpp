#include "irc.hpp"

void QUIT(irc::Command *command)
{
	if (command->getParameter()[0].length())
		command->getUser().setQuitMessage(command->getParameter()[0]);
	command->getUser().setStatus(irc::DELETE);
}
