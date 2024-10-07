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

		/*getters*/
		std::vector<irc::User*> getUsers();
		irc::User& getUser(const std::string& userNickname);
		std::string getName();
		std::string getMode();

		/*setters*/
		void setMode(bool isPlus, char mode);
		void setPassword(bool isPlus, const std::string& password);
		void setMaxUsers(bool isPlus, const std::string& maxUsers);
		void setName(std::string name);

		/** User操作 */
		bool isUser(User &user);
    bool isUser(const std::string& userNickname);
		bool isThereInvitedUser();
		void addUser(User &user);
		void delUser(User &user);
	};
}