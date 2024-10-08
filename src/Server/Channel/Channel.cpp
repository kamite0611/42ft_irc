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
irc::User& irc::Channel::getUser(const std::string& userNickname)
{
	std::map<int, irc::User*>::iterator it;
	for (it = _users.begin(); it != _users.end(); it++)
	{
		if (it->second->getNickname() == userNickname)
			break ;
	}
	return (*it->second);
}
std::string irc::Channel::getName() { return (_name); }
std::string irc::Channel::getMode() { return (_mode); }
std::string irc::Channel::getTopic() { return (_topic); }

/*
setters
*/
void	irc::Channel::setMode(bool isPlus, char mode)
{
	if (isPlus && _mode.find(mode) == std::string::npos)
		_mode += mode;
	else if (!isPlus && _mode.find(mode) != std::string::npos)
		_mode.erase(_mode.find(mode));
	if (DEBUG)
		std::cout << _name << " now mode= " << _mode << std::endl;
}
void irc::Channel::setPassword(bool isPlus, const std::string& password)
{
	if (isPlus)
		_password = password;
	else
		_password = "";
}
void irc::Channel::setMaxUsers(bool isPlus, const std::string& maxUsers)
{
	if (isPlus)
		_maxUsers = maxUsers;
	else
		_maxUsers = "";
}
void irc::Channel::setTopic(std::string topic) { _topic = topic; }



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

bool irc::Channel::isUser(const std::string& userNickname)
{
	for (std::map<int, irc::User*>::iterator it = _users.begin(); it != _users.end(); it++)
	{
		if (it->second->getNickname() == userNickname)
			return (true);
	}
	return (false);
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


void irc::Channel::write(std::string message)
{
	for (std::map<int, irc::User *>::iterator it = _users.begin(); it != _users.end(); it++)
		it->second->write(message);
}