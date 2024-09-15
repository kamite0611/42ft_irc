#pragma once

#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <vector>
#include <poll.h>

#ifndef DEBAG
#define DEBAG 0
#endif

namespace irc
{
	void printError(std::string msg, bool stop);
	std::string currentTime();
	std::string stoi(int nbr);
	void put_pfds(std::vector<pollfd> pfds);
}