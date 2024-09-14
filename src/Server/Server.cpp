#include "Server.hpp"
#include "User.hpp"
#include <sys/socket.h>
#include <netinet/in.h>

irc::Config &irc::Server::getConfig()
{
	return (this->_config);
}

irc::Display &irc::Server::getDisplay()
{
	return (this->_display);
}

irc::Server::Server() : _bootTime(irc::currentTime()), _lastPingTime(std::time(0))
{
	_display.set(0, "Welcome To Our Irc Server!");
}

/** Userの追加 */
void irc::Server::_acceptUser()
{
	/** TODO ユーザー最大数のvalidation追加 */

	struct pollfd newPoll;
	struct sockaddr_in address;
	socklen_t csin_len = sizeof(address);

	int fd = accept(_fd, (struct sockaddr *)&address, &csin_len);
	if (fd < 0)
		return;

	User *newUser = new User(fd, this, address);

	newPoll.fd = _fd;
	newPoll.events = POLLIN;
	_pfds.push_back(newPoll);
}

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
	if (setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &en, sizeof(en)) < 0)
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

	if (_pfds[0].revents == POLLIN)
		std::cout << "new User: " << _pfds[0].events << std::endl;
}
