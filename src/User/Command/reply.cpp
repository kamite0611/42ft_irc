#include "Command.hpp"

/*
:server_name code target :message
応答はこの形式で構成される
*/
void irc::Command::reply(User& user, int code)
{
	std::stringstream sscode;
	sscode << code;
	std::string scode = sscode.str();
	while (scode.length() < 3)
		scode = "0" + scode;

	std::string target;
	if (user.getStatus() == PASSWORD || user.getStatus() == REGISTER)
		target = "*";
	else
		target = user.getNickname();
	target += " ";

	user.sendTo(user, scode + " " + target + " " + getReplyMessage(code), "");
}

std::string irc::Command::getReplyMessage(int code)
{
	if (code == 401)
		return (":No such nick/channel");
}