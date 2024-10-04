#include "irc.hpp"

void MOTD(irc::Command* command)
{
	command->reply(command->getUser(), 375, command->getServer().getConfig().get("name"));
	command->reply(command->getUser(), 372, "Welcome to our IRC!");
	command->reply(command->getUser(), 376);
}