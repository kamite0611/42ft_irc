#include "Server.hpp"

irc::Config&	irc::Server::getConfig()
{
	return (this->config);
}

irc::Display&	irc::Server::getDisplay()
{
	return (this->display);
}

irc::Server::Server()
{
	display.set(0, "Welcome To Our Irc Server!");
}