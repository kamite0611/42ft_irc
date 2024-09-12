#include "Display.hpp"

void	irc::Display::clearScreen()
{
	std::cout << "\033[2J" << std::flush;
}

void	irc::Display::update()
{
	if (DEBAG)
		return ;
	clearScreen();
	for (std::map<unsigned int, std::string>::iterator it = this->lines.begin(); \
	it != this->lines.end(); it++)
		std::cout << it->second << "\033[0m" << std::endl;
}

void	irc::Display::set(unsigned int row, std::string line)
{
	if (this->lines[row] == line)
		return ;
	this->lines[row] = line;
	update();
}

void	irc::Display::remove(unsigned int row)
{
	this->lines.erase(row);
	update();
}

irc::Display::Display()
{
	update();
}

irc::Display::~Display() {}