#include "irc.hpp"

void TOPIC(irc::Command *command)
{
	if (command->getParameter().size() <= 1)
		return (command->reply(command->getUser(), 461, "TOPIC"));
	std::string channelName = command->getParameter()[0];
	if (!command->getServer().findChannel(channelName))
		return (command->reply(command->getUser(), 403, channelName));

	if (!command->getTrailer().length())
	{
		if (!command->getServer().getChannel(channelName).getTopic().length())
			return (command->reply(command->getUser(), 331, channelName));
		else
			return (command->reply(command->getUser(), 332, command->getServer().getChannel(channelName).getTopic()));
	}
	else
	{
		std::string topic = command->getTrailer();
		if (topic.length() > 300)
			return (command->reply(command->getUser(), 501, "Topic is too long"));
		if (!command->getServer().getChannel(channelName).isUser(command->getUser()))
			return (command->reply(command->getUser(), 442, channelName));
		if (command->getServer().getChannel(channelName).getMode().find('t') != std::string::npos && !command->getServer().getChannel(channelName).isAdminUser(command->getUser()))
			return (command->reply(command->getUser(), 482, channelName));
		command->getServer().getChannel(channelName).setTopic(topic);
		command->getServer().getChannel(channelName).write("TOPIC " + channelName + " :" + command->getServer().getChannel(channelName).getTopic());
	}
}