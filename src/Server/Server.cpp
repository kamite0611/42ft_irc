#include "Server.hpp"

irc::Config &irc::Server::getConfig()
{
	return (this->config);
}

irc::Display &irc::Server::getDisplay()
{
	return (this->display);
}

irc::Server::Server() : bootTime(irc::currentTime()), lastPingTime(std::time(0))
{
	display.set(0, "Welcome To Our Irc Server!");
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

	this->fd = socket(AF_INET, SOCK_STREAM, 0); // ソケット作成
	if (this->fd < 0)
		irc::printError("socket failure", true);
	int en = 1;
	if (setsockopt(this->fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &en, sizeof(en)) < 0)
		irc::printError("setsockopt failure", true);
	if (fcntl(fd, F_SETFL, O_NONBLOCK) < 0) // MacOSでは必須
		irc::printError("fcntl failure", true);
	if (bind(this->fd, (struct sockaddr *)&add, sizeof(add)) < 0) // ソケットとサーバーアドレスを関連付ける
		irc::printError("bind failure", true);
	if (listen(this->fd, SOMAXCONN) < 0)
		irc::printError("listen failure", true);

	newPoll.fd = this->fd;
	newPoll.events = POLLIN; // 接続要求の受信待ち
	this->pfds.push_back(newPoll);

	// デフォルトで設定できるモードを指定しておくが、
	// ここについては後々議論
	this->config.set("user_mode", "aiwro");
	this->config.set("channel_givemode", "Oov");
	this->config.set("channel_togglemode", "imnpt");
	this->config.set("channel_addmode", "kl");
}

void irc::Server::execute()
{
	int ping = atoi(config.get("ping").c_str());

	if (pfds[0].revents == POLLIN)
		std::cout << "pfds[0]: " << pfds[0].revents << std::endl;
}
