#include "Utils.hpp"

void	irc::printError(std::string msg, bool stop)
{
	std::cerr << msg << std::endl;
	if (stop)
		exit (1);
}

std::string	stoi(int nbr)
{
	std::stringstream	ss;
	ss << nbr;
	std::string	str = ss.str();
	return (str);
}

std::string	irc::currentTime()
{
	//Thu Sep 12 14:26:02 2024の形式
	std::time_t	time = std::time(0);
	std::tm*	localTime = std::localtime(&time);
	std::string	currentTime = asctime(localTime);

	currentTime.erase(currentTime.size() - 1); 
	return (currentTime);
}
