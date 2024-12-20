#include "Utils.hpp"
#include "Channel.hpp"

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
	std::cout << "\n----- Now pfds -----" << std::endl;
	for (std::size_t i = 0; i < pfds.size(); i++)
	{
		std::cout << "pfds[" << i << "]: " << &pfds[i] << " { fd: " << pfds[i].fd << " events: " << pfds[i].events << " }" << std::endl;
	}
}

/**
 * std::vector<irc::Channel *> を標準出力する
 */
void irc::put_channels(std::vector<irc::Channel *> channels)
{
	int i = 0;
	std::cout << "---------- channels ----------" << std::endl;
	for (std::vector<irc::Channel *>::iterator it = channels.begin(); it != channels.end(); ++it)
	{
		std::cout << "channels[" << i << "]: { name: " << (*it)->getName() << " }" << std::endl;
		i++;
	}
}

std::vector<std::string> irc::split(std::string &str, const std::string &deli)
{
	std::vector<std::string> parameters;
	size_t pos = 0;

	while ((pos = str.find(deli, pos + 1)) != std::string::npos)
	{
		parameters.push_back(str.substr(0, pos));
		str.erase(0, pos + 1);
		pos = 0;
	}
	parameters.push_back(str);
	return (parameters);
}

bool irc::isAlpha(char c)
{
	return (('a' <= c && c <= 'z') ||
					('A' <= c && c <= 'Z'));
}

bool irc::isSpecial(char c)
{
	return ('[' <= c && c <= '`');
}

bool irc::isNum(char c)
{
	return ('0' <= c && c <= '9');
}

std::string irc::toString(size_t nbr)
{
	std::ostringstream os;
	os << nbr;
	return (os.str());
}
