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

	if (IS_DEBUG)
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
	/* TODO[kkodaira] add */
}

std::vector<irc::User*> irc::Server::_getUsers()
{
	/* TODO[kkodaira] add */
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
	_config.set("user_mode", "aiwro");
	_config.set("channel_givemode", "Oov");
	_config.set("channel_togglemode", "imnpt");
	_config.set("channel_addmode", "kl");
}

void irc::Server::execute()
{
	int ping = atoi(_config.get("ping").c_str());

	if (poll(&_pfds[0], _pfds.size(), (ping * 1000) / 10) == -1)
		return;

	if (std::time(0) - _lastPingTime >= ping)
	{
		// _sendPing();
		_lastPingTime = std::time(0);
	}
	else
	{
		if (_pfds[0].revents == POLLIN)
			_acceptUser();
		for (std::vector<pollfd>::iterator it = _pfds.begin() + 1; it != _pfds.end(); it++)
		{
			if ((*it).revents == POLLIN)
				_users[(*it).fd]->receive();
		}
	}

	std::vector<irc::User*> users = getUsers();
	for (std::vector<irc::User*>::iterator it = users.begin(); it != users.end(); it++)
	{
		if ((*it)->getStatus() == DELETE)
			delUser();
	}
	// users = getUsers();
	// for (std::vector<irc::User*>::iteraotr it = users.begin(); it != users.end(); it++)
	// 	*it->push();/*メッセージ送信*/
	// users.displayUsers();/*ユーザー表示*/
}

void irc::Server::delUser()
{
	/* TODO[kkodaira] add */
}

std::vector<irc::User*> irc::Server::getUsers()
{
	std::vector<irc::User*> users;

	for (std::map<int, User*>::iterator it = _users.begin(); it != _users.end(); it++)
	{
		users.push_back(it->second);
	}
	return (users);
}

/** Getters */
irc::Config &irc::Server::getConfig() { return (this->_config); }
irc::Display &irc::Server::getDisplay() { return (this->_display); }