#include "irc.hpp"

void TOPIC(irc::Command* command)
{
	if (!command->getParameter()[0].length())
		return (command->reply(command->getUser(), 461, "TOPIC"));
	std::string channelName = command->getParameter()[0];
	irc::Channel channel;
	if (!command->getServer().isExistChannel(channelName))
		return (command->reply(command->getUser(), 403, channelName));
	else
		channel = command->getServer().getChannel(channelName);

	if (!command->getTrailer().length())
	{
		if (!channel.getTopic().length())
			return (command->reply(command->getUser(), 331, channelName));
		else
			return (command->reply(command->getUser(), 332, channel.getTopic()));
	}
	else
	{
		std::string topic = command->getTrailer();
		if (topic.length() > 300)
			return (command->reply(command->getUser(), 501, "Topic is too long"));
		if (!channel.isUser(command->getUser()))
			return (command->reply(command->getUser(), 442, channelName));
		if (channel.getMode().find('t') != std::string::npos && command->getUser().getMode().find('o') == std::string::npos)
			return (command->reply(command->getUser(), 482, channelName));
		channel.setTopic(topic);
		channel.write("TOPIC " + channelName + " :" + channel.getTopic());
	}
}