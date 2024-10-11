#include "irc.hpp"

void INVITE(irc::Command* command)
{
	std::string invitedUserNickname;
	std::string channelName;

	if (command->getParameter().size() <= 1)
		return (command->reply(command->getUser(), 461, "INVITE"));

	if (command->getServer().findUserByNickname(command->getParameter()[0]) == NULL)
		return (command->reply(command->getUser(), 401, command->getParameter()[0]));
	else
		invitedUserNickname = command->getParameter()[0];

	if (command->getServer().findChannel(command->getParameter()[1]) == NULL)
		return (command->reply(command->getUser(), 403, command->getParameter()[1]));
	else
		channelName = command->getParameter()[1];

	if (!command->getServer().findChannel(channelName)->isUser(command->getUser()))
		return (command->reply(command->getUser(), 442, channelName));

	if (command->getServer().findChannel(channelName)->getMode().find('i') != std::string::npos && command->getUser().getMode().find('o') == std::string::npos)
		return (command->reply(command->getUser(), 482, channelName));

	command->getServer().findChannel(channelName)->setInvitedUsers(command->getServer().getUser(invitedUserNickname));
	command->getUser().sendTo(command->getServer().getUser(invitedUserNickname), "INVITE " + invitedUserNickname + " " + channelName, "");
	command->reply(command->getUser(), 341, channelName, invitedUserNickname);
}