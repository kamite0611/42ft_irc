#include "irc.hpp"

void USER(irc::Command* command)
{
	if (command->getParameter().size() < 3)
		return (command->reply(command->getUser(), 461));
	if (command->getUser().getStatus() != irc::REGISTER)
		return (command->reply(command->getUser(), 462));

	
}