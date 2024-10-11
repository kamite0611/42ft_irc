#include "Channel.hpp"

irc::Channel::Channel() : _mode("n") {}

/**
 * ------------ getters ------------
 */
std::vector<irc::User *> irc::Channel::getUsers()
{
	std::vector<irc::User *> users;

	for (std::map<int, irc::User *>::iterator it = _users.begin(); it != _users.end(); it++)
		users.push_back(it->second);
	return (users);
}
irc::User &irc::Channel::getUser(const std::string &userNickname)
{
	std::map<int, irc::User *>::iterator it;
	for (it = _users.begin(); it != _users.end(); it++)
	{
		if (it->second->getNickname() == userNickname)
			break;
	}
	return (*it->second);
}
std::string irc::Channel::getName() { return (_name); }
std::string irc::Channel::getMode() { return (_mode); }
std::string irc::Channel::getTopic() { return (_topic); }
std::string irc::Channel::getMaxUsers() { return (_maxUsers); }
std::string irc::Channel::getPassword() { return (_password); }

/**
 * ------------ setters ------------
 */
void irc::Channel::setMode(bool isPlus, char mode)
{
	if (isPlus && _mode.find(mode) == std::string::npos)
		_mode += mode;
	else if (!isPlus && _mode.find(mode) != std::string::npos)
		_mode.erase(_mode.find(mode));
	if (CMD_DEBUG)
		std::cout << _name << " now mode= " << _mode << std::endl;
}
void irc::Channel::setPassword(bool isPlus, const std::string &password)
{
	if (isPlus)
		_password = password;
	else
		_password = "";
}
void irc::Channel::setMaxUsers(bool isPlus, const std::string &maxUsers)
{
	if (isPlus)
		_maxUsers = maxUsers;
	else
		_maxUsers = "";
}
void irc::Channel::setTopic(std::string topic) { _topic = topic; }

/* setters */
void irc::Channel::setName(std::string name) { _name = name; }
void irc::Channel::setInvitedUsers(irc::User& user) { _invitedUsers.push_back(&user); }


/**
 * ------------ User Functions ------------
 */
/** User 存在チェック */
bool irc::Channel::isUser(irc::User &user)
{
	return (_users.find(user.getFd()) != _users.end());
}

/** User 名前で存在チェック */
bool irc::Channel::isUserByName(const std::string &userNickname)
{
	for (std::map<int, irc::User *>::iterator it = _users.begin(); it != _users.end(); it++)
	{
		if (it->second->getNickname() == userNickname)
			return (true);
	}
	return (false);
}
/** User 削除 */
void irc::Channel::delUser(User &user)
{
	_users.erase(user.getFd());
	/** 管理者リストにいる場合も削除 */
	std::vector<int>::iterator it = std::find(_adminUserFds.begin(), _adminUserFds.end(), user.getFd());
	if (it != _adminUserFds.end())
		_adminUserFds.erase(it);
}

/** User 検索 */
irc::User *irc::Channel::findUserByNickname(std::string name)
{
	std::vector<irc::User *> users = getUsers();
	for (std::vector<irc::User *>::iterator it = users.begin(); it != users.end(); it++)
	{
		if ((*it)->getNickname() == name)
			return *it;
	}
	return NULL;
}

/** User 追加 */
void irc::Channel::addUser(User &user, bool isAdmin)
{
	_users[user.getFd()] = &user;
	if (isAdmin)
		_adminUserFds.push_back(user.getFd());
}

/** Userが管理者かどうか */
bool irc::Channel::isAdminUser(irc::User &user)
{
	std::vector<int>::iterator it = std::find(_adminUserFds.begin(), _adminUserFds.end(), user.getFd());
	return it != _adminUserFds.end();
}

/**
 * ------------ Invite Functions ------------
 */
/** 対象Userが招待済みかどうか */
bool irc::Channel::isInvitedUser(irc::User &user) { return std::find(_invitedUsers.begin(), _invitedUsers.end(), &user) != _invitedUsers.end(); }

/** Userを招待する */
void irc::Channel::invitedUser(irc::User &user) { _invitedUsers.push_back(&user); }

/** ユーザーの招待を取り消す */
void irc::Channel::removeUserInvite(irc::User &user)
{
	std::vector<User *>::iterator it = std::find(_invitedUsers.begin(), _invitedUsers.end(), &user);
	if (it != _invitedUsers.end())
		_invitedUsers.erase(it);
}

/** すでに招待済みのユーザーがいるかどうか */
bool irc::Channel::isThereInvitedUser()
{
	return (_invitedUsers.size());
}

void irc::Channel::write(std::string message)
{
	for (std::map<int, irc::User *>::iterator it = _users.begin(); it != _users.end(); it++)
		it->second->write(message);
}

/**
 *
 */
/** 全員に向け発言 */
void irc::Channel::broadcast(User &user, std::string message)
{
	for (std::map<int, User *>::iterator it = _users.begin(); it != _users.end(); ++it)
		user.sendTo(*it->second, message);
}
