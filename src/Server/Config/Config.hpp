#pragma once

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <exception>
#include <sstream>

namespace	irc
{
	class	Config
	{
	private:
		std::map<std::string, std::string>	values;
	public:
		Config();
		Config(std::string fileName);
		~Config();

		void		init(std::string fileName);
		void		set(std::string key, std::string value);
		std::string	get(std::string key);
	};
}