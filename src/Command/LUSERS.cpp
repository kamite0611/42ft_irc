#include "irc.hpp"

void LUSERS(irc::Command* command)
{
	command->reply(command->getUser(), 251, irc::toString(command->getServer().getVisibleCount()), \
		irc::toString(command->getServer().getInvisibleCount()), "1");
	command->reply(command->getUser(), 252, irc::toString(command->getServer().getOperatorCount()));
	command->reply(command->getUser(), 253, irc::toString(command->getServer().getUnknownCount()));
	command->reply(command->getUser(), 254, irc::toString(command->getServer().getChannels().size()));
	command->reply(command->getUser(), 255, irc::toString(command->getServer().getUsers().size()), "0"); /*接続されているサーバーは自身を除くので0*/
}
