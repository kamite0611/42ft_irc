#pragma once

#include "Config.hpp"
#include "Display.hpp"

namespace	irc
{
	class	Server
	{
	private:
		Config	config;
		Display	display;
	public:
		Server();

		irc::Config&	getConfig();
		irc::Display&	getDisplay();
		// void			init();
	};
}