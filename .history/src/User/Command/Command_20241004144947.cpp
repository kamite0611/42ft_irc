#include "Command.hpp"

irc::Command::Command(User* user, Server* server, std::string message): \
_user(user), _server(server)
{
	std::string delimiter(":");
	size_t pos;
	if ((pos = message.find(delimiter)) != std::string::npos)
	{
		std::string tmp = message.substr(0, pos + 1);
		message.erase(0, pos);
		_trailer = message; /*trailerは:を含まない*/
		message = tmp; /*messageも:を含まない*/
	}

	_parameters = irc::split(message, " ");
	_prefix = _parameters[0];
	_parameters.erase(_parameters.begin());

	for (size_t i = 0; i < _prefix.length(); i++)
		_prefix[i] = std::toupper(_prefix[i]);
}

irc::Command::~Command() {}

/*getters*/
std::vector<std::string>& irc::Command::getParameter() { return (_parameters); }
irc::User& irc::Command::getUser() { return (*_user); }
irc::Server& irc::Command::getServer() { return (*_server); }
std::string& irc::Command::getPrefix() { return (_prefix); }
std::string& irc::Command::getTrailer() { return (_)}