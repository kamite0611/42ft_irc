#pragma once

#include "Utils.hpp"
#include <map>
#include <iostream>
#include <string>

namespace	irc
{
	class	Display
	{
	private:
		std::map<unsigned int, std::string>	lines;
	public:
		Display();
		~Display();

		void	clearScreen();
		void	update();
		void	set(unsigned int row, std::string line);
		void	remove(unsigned int row);
	};
}