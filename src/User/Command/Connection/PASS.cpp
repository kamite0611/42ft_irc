#include "irc.hpp"

void PASS(irc::Command *command)
{
	if (!command->getParameter()[0].length())
		command->reply(command->getUser(), 461);
	else if (command->getUser().getStatus() != irc::PASSWORD)
		command->reply(command->getUser(), 462);
	else if (command->getParameter()[0] != command->getServer().getConfig().get("password"))
		command->reply(command->getUser(), 464);
	else if (command->getParameter()[0] == command->getServer().getConfig().get("password"))
	{
		std::cout << "PASSWORD was right!" << std::endl;
		command->getUser().setStatus(irc::REGISTER);
	}
}