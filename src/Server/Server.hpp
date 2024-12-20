#pragma once

#include "Config.hpp"
#include "User.hpp"
#include <ctime>
#include <poll.h>
#include <vector>
#include <sys/socket.h>
#include <sys/types.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <map>
#include <algorithm>

namespace irc
{
	class User;
	class Channel;

	class Server
	{
	private:
		Config _config;

		std::map<int, User *> _users;
		std::map<std::string, Channel> _channels;
		int _fd;
		std::string _bootTime;
		std::time_t _lastPingTime;
		std::vector<pollfd> _pfds;

		void _acceptUser();							 /** Userの追加 */
		void _disconnectUser();					 /** Userの削除 */
		void _sendPing();								 /** pingの送信*/
		std::vector<User *> _getUsers(); /** User列の取得*/

	public:
		Server();
		~Server();

		/** Getters */
		irc::Config &getConfig();
		std::vector<irc::User *> getUsers();
		std::vector<irc::Channel *> getChannels();
		irc::Channel &getChannel(const std::string &name);
		std::string &_getBootTime();
		size_t getVisibleCount();
		size_t getInvisibleCount();
		size_t getOperatorCount();
		size_t getUnknownCount();
		size_t getClientCount();
		std::time_t getLastPingTime();
		irc::User& getUser(const std::string& name);

		/** サーバー実行 */
		void init();
		void execute();

		/*User操作*/
		void delUser(irc::User &user);
		irc::User *findUserByNickname(std::string name);

		/*Channel操作*/
		irc::Channel *findChannel(std::string channelName);
		irc::Channel &createOrFindChannel(std::string channelName);
		void delChannel(irc::Channel &channel);
	};
}
