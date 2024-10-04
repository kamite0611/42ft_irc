#include "irc.hpp"

void LUSERS(irc::Command* command)
{
	command->reply(command->getUser(), 251, std::to_string(command->getServer().getVisibleCount()), \
		std::to_string(command->getServer().getInvisibleCount()), "1");
	command->reply(command->getUser(), 252, std::to_string(command->getServer().getOperatorCount()));
	command->reply(command->getUser(), 253, std::to_string(command->getServer().getUnknownCount()));
	command->reply(command->getUser(), 254, std::to_string(command->getServer().getChannels().size()));
	command->reply(command->getUser(), 255, std::to_string(command->getServer().getUsers().size()), "0"); /*接続されているサーバーは自身を除くので0*/
}
