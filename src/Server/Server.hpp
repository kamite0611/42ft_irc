#pragma once

#include "Config.hpp"
#include "Display.hpp"
#include <ctime>
#include <poll.h>
#include <vector>
#include <sys/socket.h>
#include <sys/types.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdlib.h>

namespace irc
{
	class Server
	{
	private:
		Config config;
		Display display;
		// map<int, User*> 			users;
		// map<std::string, Channel>	channels;
		int fd;
		std::string bootTime;
		std::time_t lastPingTime;
		std::vector<pollfd> pfds;

	public:
		Server();

		irc::Config &getConfig();
		irc::Display &getDisplay();
		void init();
		void execute();
	};
}
