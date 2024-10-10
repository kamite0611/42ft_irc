#include "Server.hpp"
#include "irc.hpp"
#include <sys/socket.h>
#include <netinet/in.h>

irc::Server::Server() : _bootTime(irc::currentTime()), _lastPingTime(std::time(0))
{
	_display.set(0, "Welcome To Our Irc Server!");
}

/*---------------- Private Functions  ----------------*/

/**
 * Userの追加
 */
void irc::Server::_acceptUser()
{
	struct sockaddr_in address;
	socklen_t csin_len = sizeof(address);

	int fd = accept(_fd, (struct sockaddr *)&address, &csin_len);
	if (fd < 0)
		return;

	User *newUser = new User(fd, this, address);
	_users[fd] = newUser;

	struct pollfd newPoll;
	newPoll.fd = fd;
	newPoll.events = POLLIN;
	_pfds.push_back(newPoll);

	irc::put_pfds(_pfds);

	if (DEBUG)
		std::cout << "newUser[" << fd << "]: " << newUser << " accept success!!" << std::endl;
}

/**
 * Userの削除
 */
void irc::Server::_disconnectUser()
{
	/** TODO[akamite] add */
}

void irc::Server::_sendPing()
{
	std::time_t currentTime = std::time(0);
	for (std::map<int, User *>::iterator it = _users.begin(); it != _users.end(); it++)
	{
		std::cout << "currentTime=" << currentTime << std::endl;
		if ((currentTime - it->second->getLastPingTime()) >= atoi(_config.get("timeout").c_str()))
		{
			it->second->setStatus(DELETE);
			it->second->setQuitMessage("Ping timeout");
		}
		else
		{
			if (it->second->getStatus() == ONLINE)
				it->second->write("PING " + _config.get("name"));
		}
	}
}

std::vector<irc::User *> irc::Server::_getUsers()
{
	/* TODO[kkodaira] add */
	return std::vector<irc::User *>();
}

/*---------------- Public Functions  ----------------*/

void irc::Server::init()
{
	struct pollfd newPoll;
	struct sockaddr_in add;
	/*
	struct sockaddr_in
	{
		short sin_family;        //アドレスファミリー (使用されるアドレスの種類)
		unsigned int sin_port;   //ポート番号
		struct in_addr sin_addr; //IPv4アドレス
		char sin_zero[8]         //パディング(通常は0)
	}
	*/

	add.sin_family = AF_INET; // IPv4
	add.sin_port = htons(atoi(this->getConfig().get("port").c_str()));
	add.sin_addr.s_addr = INADDR_ANY; // ローカルマシンのすべてのアドレス受け入れ

	_fd = socket(AF_INET, SOCK_STREAM, 0); // ソケット作成
	if (_fd < 0)
		irc::printError("socket failure", true);
	int en = 1;
	if (setsockopt(_fd, SOL_SOCKET, IS_MAC ? SO_REUSEPORT : SO_REUSEADDR | SO_REUSEPORT, &en, sizeof(en)) < 0)
		irc::printError("setsockopt failure", true);
	if (fcntl(_fd, F_SETFL, O_NONBLOCK) < 0) // MacOSでは必須
		irc::printError("fcntl failure", true);
	if (bind(_fd, (struct sockaddr *)&add, sizeof(add)) < 0) // ソケットとサーバーアドレスを関連付ける
		irc::printError("bind failure", true);
	if (listen(_fd, SOMAXCONN) < 0)
		irc::printError("listen failure", true);

	newPoll.fd = _fd;
	newPoll.events = POLLIN; // 接続要求の受信待ち
	_pfds.push_back(newPoll);

	// デフォルトで設定できるモードを指定しておくが、
	// ここについては後々議論
	_config.set("user_mode", "io");
	_config.set("channel_givemode", "o");
	_config.set("channel_togglemode", "it");
	_config.set("channel_addmode", "kl");
}

void irc::Server::execute()
{
	int ping = atoi(_config.get("ping").c_str());

	if (poll(&_pfds[0], _pfds.size(), (ping * 1000) / 10) == -1)
		return;

	if (std::time(0) - _lastPingTime >= ping)
	{
		_sendPing();
		_lastPingTime = std::time(0);
	}
	else
	{
		if (_pfds[0].revents == POLLIN)
			_acceptUser();
		else
		{
			for (std::vector<pollfd>::iterator it = _pfds.begin(); it != _pfds.end(); ++it)
			{
				if ((*it).revents == POLLIN)
					_users[(*it).fd]->receive();
			}
		}
	}

	std::vector<irc::User *> users = getUsers();
	for (std::vector<irc::User *>::iterator it = users.begin(); it != users.end(); it++)
	{
		if ((*it)->getStatus() == DELETE)
			delUser(*(*it));
	}
	users = getUsers();
	for (std::vector<irc::User *>::iterator it = users.begin(); it != users.end(); it++)
		(*it)->push(); /*メッセージ送信*/
									 // users.displayUsers();/*ユーザー表示*/
	if (DEBUG)
	{
		std::cout << "\n=====Now User=====\n";
		for (std::map<int, User *>::iterator it = _users.begin(); it != _users.end(); it++)
			std::cout << "User=" << it->second->getPrefix() << std::endl;
	}
}

void irc::Server::delUser(irc::User &user)
{
	std::vector<irc::User *> receipients;

	receipients.push_back(&user);
	std::vector<irc::Channel> emptyChannels;
	for (std::map<std::string, Channel>::iterator it = _channels.begin(); it != _channels.end(); it++)
	{
		if (it->second.isUser(user))
		{
			it->second.delUser(user);
			if (it->second.getUsers().size() == 0)
				emptyChannels.push_back(it->second);
			else
			{
				std::vector<irc::User *> users = it->second.getUsers();
				for (std::vector<irc::User *>::iterator itUser = users.begin(); itUser != users.end(); itUser++)
				{
					if (std::find(receipients.begin(), receipients.end(), *itUser) != receipients.end())
						receipients.push_back(*itUser);
				}
			}
		}
	}
	for (std::vector<irc::Channel>::iterator it = emptyChannels.begin(); it != emptyChannels.end(); it++)
	{
		/*招待されているユーザーがいるときは消さない*/
		if (!(*it).isThereInvitedUser())
			delChannel(*it);
	}

	for (std::vector<irc::User *>::iterator it = receipients.begin(); it != receipients.end(); it++)
		user.write("Quit: " + (*it)->getQuitMessage());
	user.push();
	_users.erase(user.getFd());
	for (std::vector<pollfd>::iterator it = _pfds.begin(); it != _pfds.end(); it++)
	{
		if ((*it).fd == user.getFd())
		{
			_pfds.erase(it);
			break;
		}
	}
	delete &user;
}

void irc::Server::delChannel(irc::Channel &channel)
{
	_channels.erase(channel.getName());
}

/** Getters */
irc::Config &irc::Server::getConfig() { return (this->_config); }
irc::Display &irc::Server::getDisplay() { return (this->_display); }
std::vector<irc::User *> irc::Server::getUsers()
{
	std::vector<irc::User *> users;

	for (std::map<int, User *>::iterator it = _users.begin(); it != _users.end(); it++)
	{
		users.push_back(it->second);
	}
	return (users);
}

/**
 * Getter _channelsを取得する
 * std::map<チャンネル名, Obj> → std::vector<irc::Channel *> で出力される
 */
std::vector<irc::Channel *> irc::Server::getChannels()
{
	std::vector<irc::Channel *> channels;

	for (std::map<std::string, irc::Channel>::iterator it = _channels.begin(); it != _channels.end(); it++)
		channels.push_back(&(*it).second);
	return (channels);
}
irc::Channel &irc::Server::getChannel(const std::string &name) { return (_channels[name]); }

std::string &irc::Server::_getBootTime() { return (_bootTime); }
size_t irc::Server::getVisibleCount()
{
	size_t count = 0;
	for (std::map<int, User *>::iterator it = _users.begin(); it != _users.end(); it++)
	{
		if (it->second->getMode().find('i') == std::string::npos)
			count++;
	}
	return (count);
}
size_t irc::Server::getInvisibleCount()
{
	size_t count = 0;
	for (std::map<int, User *>::iterator it = _users.begin(); it != _users.end(); it++)
	{
		if (it->second->getMode().find('i') != std::string::npos)
			count++;
	}
	return (count);
}
size_t irc::Server::getOperatorCount()
{
	size_t count = 0;
	for (std::map<int, User *>::iterator it = _users.begin(); it != _users.end(); it++)
	{
		if (it->second->getMode().find('o') != std::string::npos)
			count++;
	}
	return (count);
}
size_t irc::Server::getUnknownCount()
{
	size_t count = 0;
	for (std::map<int, User *>::iterator it = _users.begin(); it != _users.end(); it++)
	{
		if (it->second->getStatus() != ONLINE)
			count++;
	}
	return (count);
}
size_t irc::Server::getClientCount()
{
	return 0;
}
std::time_t irc::Server::getLastPingTime() { return (_lastPingTime); }

/**
 * -------- Channels func ---------
 */
/** チャンネルを名前から取得 */
irc::Channel *irc::Server::findChannel(std::string channelName)
{
	std::map<std::string, Channel>::iterator it = _channels.find(channelName);

	if (it != _channels.end())
		return &(it->second);
	return NULL;
}

/** チャンネルがある場合は取得、ない場合は作成 */
irc::Channel &irc::Server::createOrFindChannel(std::string channelName)
{
	bool exist = !!findChannel(channelName);

	std::cout << "exist: " << exist << std::endl;
	Channel &channel = _channels[channelName];
	if (!exist)
	{
		channel.setName(channelName);
	}

	return channel;
}