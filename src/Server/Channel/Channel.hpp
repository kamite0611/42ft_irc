#pragma once

#include <string>
#include <map>
#include "User.hpp"

namespace irc
{
	class Channel
	{
	private:
		std::string _name;
		std::string _topic;
		std::map<int, irc::User *> _users;
		std::string _mode;
		std::map<int, std::string> _useMode;
		std::string _password;
		std::string _maxUsers;
		std::vector<irc::User *> _invitedUser;

	public:
		Channel();

		/* getters */
		std::vector<irc::User *> getUsers();
		std::string getName() { return _name; };

		/* setters */
		void setName(std::string name);

		bool isUser(User &user);
	};
}