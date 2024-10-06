#include "Channel.hpp"

irc::Channel::Channel() : _mode("n") {}

/*getters*/
std::vector<irc::User *> irc::Channel::getUsers()
{
	std::vector<irc::User *> users;

	for (std::map<int, irc::User *>::iterator it = _users.begin(); it != _users.end(); it++)
		users.push_back(it->second);
	return (users);
}
std::string irc::Channel::getName() { return (_name); }

/* setters */
void irc::Channel::setName(std::string name) { _name = name; }

/**
 * ------------ User Functions ------------
 */
/** User 存在チェック */
bool irc::Channel::isUser(irc::User &user)
{
	return (_users.find(user.getFd()) != _users.end());
}

/** User 削除 */
void irc::Channel::delUser(User &user) { _users.erase(user.getFd()); }

/** User 追加 */
void irc::Channel::addUser(User &user) { _users[user.getFd()] = &user; }

/** User すでに招待済みか */
bool irc::Channel::isThereInvitedUser()
{
	return (_invitedUser.size());
}
