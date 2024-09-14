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
	class Server
	{
	private:
		Config _config;
		Display _display;

		std::map<int, User *> _users;
		// map<std::string, Channel>	channels;
		int _fd;
		std::string _bootTime;
		std::time_t _lastPingTime;
		std::vector<pollfd> _pfds;

		/** Userの追加 */
		void _acceptUser();

	public:
		Server();

		/** Getters */
		irc::Config &getConfig();
		irc::Display &getDisplay();
		void init();

		/** サーバー実行 */
		void execute();
	};
}
