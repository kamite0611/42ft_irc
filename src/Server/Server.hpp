#pragma once

#include "Config.hpp"
#include "User.hpp"
#include "Display.hpp"
#include <ctime>
#include <poll.h>
#include <vector>
#include <sys/socket.h>
#include <sys/types.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <map>

namespace irc
{
	class User;
	class Channel;

	class Server
	{
	private:
		Config _config;
		Display _display;

		std::map<int, User *> _users;
		std::map<std::string, Channel*>	_channels;
		int _fd;
		std::string _bootTime;
		std::time_t _lastPingTime;
		std::vector<pollfd> _pfds;

		void _acceptUser();			/** Userの追加 */
		void _disconnectUser(); /** Userの削除 */
		void _sendPing(); /*pingの送信*/
		std::vector<User*> _getUsers(); /*User列の取得*/

	public:
		Server();

		/** Getters */
		irc::Config &getConfig();
		irc::Display &getDisplay();
		std::vector<irc::User*> getUsers();
		std::vector<irc::Channel*> getChannels();
		irc::Channel& getChannel(const std::string& name);
		std::string& _getBootTime();
		size_t getVisibleCount();
		size_t getInvisibleCount();
		size_t getOperatorCount();
		size_t getUnknownCount();
		size_t getClientCount();

		/** サーバー実行 */
		void init();
		void execute();

		/*User操作*/
		void delUser(irc::User& user);

		/*Channel操作*/
		void delChannel(irc::Channel& channel);
	};
}
