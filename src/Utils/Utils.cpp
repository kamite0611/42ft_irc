#include "Utils.hpp"

void	irc::printError(std::string msg, bool stop)
{
	std::cerr << msg << std::endl;
	if (stop)
		exit (1);
}