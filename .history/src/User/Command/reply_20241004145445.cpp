#include "Command.hpp"

/*
:server_name code target :message
応答はこの形式で構成される
*/

void irc::Command::reply(User& user, int code, const std::string& arg1)
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

	user.sendTo(user, scode + " " + target + " " + getReplyMessage(code, arg1), "");
}
std::string irc::Command::getReplyMessage(int code, const std::string& arg1)
{
	if (code == 401)
		return (":No such nick/channel");
	else if (code == 431)
		return (":No nickname given");
	else if (code == 432)
		return (arg1 + " :Erroneus nickname");
	else if (code == 433)
		return (arg1 + " :Nickname is already in use");
	else if (code == 461)
		return ()
	else if (code == 484)
		return (":Your connection is restricted!");
}
