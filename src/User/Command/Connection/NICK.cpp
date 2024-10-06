#include "irc.hpp"

void NICK(irc::Command* command)
{
	if (!command->getParameter()[0].length())
		return (command->reply(command->getUser(), 431));
	// if (command->getUser().getMode().find('r') != std::string::npos)
	// 	return (command->reply(command->getUser(), 484));

	/*nickname精査*/
	std::string nickname;
	nickname = command->getParameter()[0];
	if (nickname.length() > 9)
		return (command->reply(command->getUser(), 432, nickname));
	int i = 0;
	if (!irc::isAlpha(nickname[i]) && !irc::isSpecial(nickname[i]))
		return (command->reply(command->getUser(), 432, nickname));
	i++;
	while (nickname[i])
	{
		if (!irc::isAlpha(nickname[i]) && !irc::isSpecial(nickname[i]) && !irc::isNum(nickname[i]))
			return (command->reply(command->getUser(), 432, nickname));
		i++;
	}
	std::vector<irc::User*> users = command->getServer().getUsers();
	for (std::vector<irc::User*>::iterator it = users.begin(); it != users.end(); it++)
	{
		if ((*it)->getNickname() == nickname)
			return (command->reply(command->getUser(), 433, nickname));
	}
	if (command->getUser().getNickname().length())
		command->getUser().setPastNickname(command->getUser().getNickname());

	std::vector<irc::User*> recipient;
	std::vector<irc::Channel*> channels = command->getServer().getChannels();
	for (std::vector<irc::Channel*>::iterator it = channels.begin(); it != channels.end(); it++)
	{
		if ((*it)->isUser(command->getUser()))
		{
			std::vector<irc::User*> users = (*it)->getUsers();
			for (std::vector<irc::User*>::iterator it = users.begin(); it != users.end(); it++)
			{
				if (std::find(recipient.begin(), recipient.end(), *it) == recipient.end())
					recipient.push_back(*it);
			}
		}
	}

	std::string message = "NICK :" + nickname;
	for (std::vector<irc::User*>::iterator it = recipient.begin(); it != recipient.end(); it++)
		command->getUser().sendTo(*(*it), message, "");
	command->getUser().setNickname(nickname);
}
