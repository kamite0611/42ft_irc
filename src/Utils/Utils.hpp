#pragma once

#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <vector>
#include <poll.h>

#ifndef DEBUG
#define DEBUG 0
#endif

namespace irc
{
	void printError(std::string msg, bool stop);
	std::string currentTime();
	std::string stoi(int nbr);
	void put_pfds(std::vector<pollfd> pfds);
	// void put_channels(std::vector<irc::Channel *> channels);

	std::vector<std::string> split(std::string &str, const std::string &deli);
	bool isAlpha(char c);
	bool isSpecial(char c);
	bool isNum(char c);
}
