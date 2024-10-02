#include "irc.hpp"

void    CAP(irc::Command* command)
{
	if (command->getParameter()[0] == "LS")
	{
		command->getUser().sendTo(command->getUser(), "CAP * LS :", "");
		command->getUser().setStatus(irc::PASSWORD);
	}
	else
		command->getUser().sendTo(command->getUser(), "CAP * NAK :", "");
}