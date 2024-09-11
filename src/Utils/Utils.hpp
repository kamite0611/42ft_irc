#pragma once

#include <string>
#include <iostream>
#include <cstdlib>

#ifndef DEBAG
# define DEBAG 0
#endif

namespace	irc
{
	void	printError(std::string msg, bool stop);

}