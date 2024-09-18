#pragma once

#include <string>
#include <map>

irc	namespace
{
	class	Channel
	{
	private:
		std::string					_name;
		std::string					_topic;
		// std::map<int, irc::User*>	_users;
		std::string					_mode;
		std::map<int, std::string>	_useMode;
		std::string					_password;
		std::string					_maxUsers;
		// std::vector<irc::User*>		_invitedUser;
	public:
		Channel();
	}
}