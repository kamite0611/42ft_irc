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
		/** 管理者リスト */
		std::vector<int> _adminUserFds;
		std::string _password;
		std::string _maxUsers;
		std::vector<irc::User *> _invitedUsers;

	public:
		Channel();

		/*getters*/
		std::vector<irc::User *> getUsers();
		irc::User &getUser(const std::string &userNickname);
		std::string getName();
		std::string getMode();
		std::string getTopic();

		/*setters*/
		void setMode(bool isPlus, char mode);
		void setPassword(bool isPlus, const std::string &password);
		void setMaxUsers(bool isPlus, const std::string &maxUsers);
		void setName(std::string name);
		void setTopic(std::string topic);

		/** User操作 */
		bool isUser(User &user);
		bool isUserNyName(const std::string &userNickname);
		void addUser(User &user, bool isAdmin);
		void delUser(User &user);

		/** User招待周り */
		bool isInvitedUser(irc::User &user);
		void invitedUser(irc::User &user);
		void removeUserInvite(irc::User &user);
		bool isThereInvitedUser();

		void write(std::string message);

		/** 全員に向け発言 */
		void broadcast(User &user, std::string message);
	};
}