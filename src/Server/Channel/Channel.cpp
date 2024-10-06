#include "Channel.hpp"

irc::Channel::Channel(): _mode("n") {}

/*getters*/
std::vector<irc::User*> irc::Channel::getUsers()
{
	std::vector<irc::User*> users;

	for (std::map<int, irc::User*>::iterator it = _users.begin(); it != _users.end(); it++)
		users.push_back(it->second);
	return (users);
}
std::string irc::Channel::getName() { return (_name); }

bool irc::Channel::isUser(irc::User& user)
{
	return (_users.find(user.getFd()) != _users.end());
}

bool irc::Channel::isThereInvitedUser()
{
	return (_invitedUser.size());
}

void irc::Channel::delUser(User& user)
{
	_users.erase(user.getFd());
}