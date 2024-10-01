#include "Utils.hpp"

void irc::printError(std::string msg, bool stop)
{
	std::cerr << msg << std::endl;
	if (stop)
		exit(1);
}

std::string stoi(int nbr)
{
	std::stringstream ss;
	ss << nbr;
	std::string str = ss.str();
	return (str);
}

std::string irc::currentTime()
{
	// Thu Sep 12 14:26:02 2024の形式
	std::time_t time = std::time(0);
	std::tm *localTime = std::localtime(&time);
	std::string currentTime = asctime(localTime);

	currentTime.erase(currentTime.size() - 1);
	return (currentTime);
}

/**
 * std::vector<pollfd> を標準出力する
 */
void irc::put_pfds(std::vector<pollfd> pfds)
{
	std::cout << std::endl
						<< "----------- pfds -----------" << std::endl;
	for (std::size_t i = 0; i < pfds.size(); i++)
	{
		std::cout << "pfds[" << i << "]: " << &pfds[i] << " { fd: " << pfds[i].fd << " events: " << pfds[i].events << " }" << std::endl;
	}
}