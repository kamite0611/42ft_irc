#pragma once

#include <string>
#include <map>

irc	namespace
{
	class	Channel
	{
	private:
		std::string					name;
		std::string					topic;
		// std::map<int, irc::User*>	users;
		std::string					mode;
		std::map<int, std::string>	useMode;
		std::string					password;
		std::string					maxUsers;
		// std::vector<irc::User*>		invitedUser;
	public:
		Channel();
	}
}