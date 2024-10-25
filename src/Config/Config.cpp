#include "Config.hpp"

void	irc::Config::init(std::string fileName)
{
	std::ifstream	file(fileName.c_str());
	if (!file.is_open())
		irc::printError("cofig file opening failure", true);
	std::string	line;
	while (std::getline(file, line))
	{
		int	delPos;
		if ((delPos = line.find("=")) == std::string::npos)
			continue ;
		std::string	key = line.substr(0, delPos);
		std::string value = line.substr(delPos + 1);

		if (value.compare(0, 2, "./") == 0)
		{
			std::ifstream	contentFile(value.c_str());
			if (!contentFile.is_open())
				irc::printError("content file opening failure", true);
			std::string	contentLine;
			std::getline(contentFile, contentLine);
			value = contentLine;
			while (std::getline(contentFile, contentLine))
			{
				value += "\n";
				value += contentLine;
			}
		}
		this->_values[key] = value;
	}
	file.close(); //スコープを抜けると自動でcloseされる
}

void	irc::Config::set(std::string key, std::string value)
{
	this->_values[key] = value;
}

std::string	irc::Config::get(std::string key)
{
	return (this->_values[key]);
}

irc::Config::Config()
{
	init("./configs/default.config");
}

irc::Config::Config(std::string fileName)
{
	init(fileName);
}

irc::Config::~Config() {}