#include "irc.hpp"

bool inLimit(std::string num)
{
	size_t i = 0;
	if (num[i] == '-')
		return (false);
	if (num[i] == '+')
		i++;
	size_t number = 0;
	while (num[i])
	{
		if (!irc::isNum(num[i]))
			return (false);
		number = (number * 10) + (num[i] - '0');
		if (number > 200)
			return (false);
		i++;
	}
	if (number > 200 || number == 0)
		return (false);
	return (true);
}

void setting(irc::Command *command, bool isPlus, std::string &settingMode, irc::Channel &channel)
{
	if (!channel.isAdminUser(command->getUser()))
		return (command->reply(command->getUser(), 482, channel.getName()));
	for (size_t i = 0; i < settingMode.size(); i++)
	{
		if (command->getServer().getConfig().get("channel_givemode").find(settingMode[i]) != std::string::npos)
		{
			if (command->getParameter().size() <= 2)
			{
				command->reply(command->getUser(), 461, command->getPrefix());
				continue;
			}
			else
			{
				std::string userNickname = command->getParameter()[2];
				if (!channel.isUserByName(userNickname))
				{
					command->reply(command->getUser(), 441, userNickname, channel.getName());
					continue;
				}
				channel.addUser(channel.getUser(userNickname), true);
				channel.getUser(userNickname).setMode(true, settingMode[i]);
			}
		}
		else if (command->getServer().getConfig().get("channel_togglemode").find(settingMode[i]) != std::string::npos)
		{
			channel.setMode(isPlus, settingMode[i]);
		}
		else if (command->getServer().getConfig().get("channel_addmode").find(settingMode[i]) != std::string::npos)
		{
			if (settingMode[i] == 'k')
			{
				if (isPlus && command->getParameter().size() <= 2)
				{
					command->reply(command->getUser(), 461, command->getPrefix());
					continue;
				}
				else if (isPlus && command->getParameter()[2].size() > 32)
				{
					command->reply(command->getUser(), 503, "Password is too long");
				}
				channel.setMode(isPlus, settingMode[i]);
				channel.setPassword(isPlus, command->getParameter()[2]);
			}
			else if (settingMode[i] == 'l')
			{
				if (isPlus && command->getParameter().size() <= 2)
				{
					command->reply(command->getUser(), 461, command->getPrefix());
					continue;
				}
				else if (isPlus && !inLimit(command->getParameter()[2]))
				{
					command->reply(command->getUser(), 503, "invalid parameter");
				}
				channel.setMode(isPlus, settingMode[i]);
				channel.setMaxUsers(isPlus, command->getParameter()[2]);
			}
		}
		else
		{
			command->reply(command->getUser(), 472);
		}
	}
	if (CMD_DEBUG)
		std::cout << channel.getName() << "'s mode=" << channel.getMode() << std::endl;
}

void MODE(irc::Command *command)
{
	if (!command->getParameter()[0].size())
		return (command->reply(command->getUser(), 461, command->getPrefix()));
	if (command->getParameter()[0][0] != '#')
		return;

	if (command->getParameter().size() > 1)
	{
		std::string channelName = command->getParameter()[0];
		std::string settingMode = command->getParameter()[1];
		if (command->getServer().findChannel(channelName))
		{
			if (DEBUG)
				std::cout << "settingMode=" << settingMode << std::endl;
			size_t i = 0;
			while (settingMode[i])
			{
				std::string nowSettingMode = "";
				if (settingMode[i] == '-')
				{
					i++;
					while (settingMode[i] && settingMode[i] != '+' && settingMode[i] != '-')
					{
						nowSettingMode += settingMode[i];
						i++;
					}
					setting(command, false, nowSettingMode, command->getServer().getChannel(channelName));
				}
				else
				{
					if (settingMode[i] == '+')
						i++;
					while (settingMode[i] && settingMode[i] != '+' && settingMode[i] != '-')
					{
						nowSettingMode += settingMode[i];
						i++;
					}
					setting(command, true, nowSettingMode, command->getServer().getChannel(channelName));
				}
			}
		}
		else
		{
			command->reply(command->getUser(), 403, channelName);
			if (DEBUG)
				std::cout << channelName << " is not exist." << std::endl;
			return;
		}
	}
	else
	{
		std::string channelName = command->getParameter()[0];
		if (command->getServer().findChannel(channelName))
		{
			command->reply(command->getUser(), 324, channelName, command->getServer().getChannel(channelName).getMode());
		}
		else
		{
			command->reply(command->getUser(), 403, channelName);
			if (DEBUG)
				std::cout << channelName << " is not exist." << std::endl;
			return;
		}
	}
}

/*
Parameters:  <channel> {[+|-]|o|p|s|i|t|n|b|v} [<limit>] [<user>] [<ban mask>]
*/