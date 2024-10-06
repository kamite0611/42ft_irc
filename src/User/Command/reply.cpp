#include "Command.hpp"

/*
:server_name code target :message
応答はこの形式で構成される
*/

void irc::Command::reply(User& user, int code, const std::string& arg1, \
											   const std::string& arg2, \
											   const std::string& arg3, \
											   const std::string& arg4)
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

	user.sendTo(user, scode + " " + target + " " + getReplyMessage(code, arg1, arg2, arg3, arg4), "");
}
std::string irc::Command::getReplyMessage(int code, const std::string& arg1, \
													const std::string& arg2, \
													const std::string& arg3, \
													const std::string& arg4)
{
	if (code == 1)
		return (":Welcome to the Internet Relay Network " + arg1);
	else if (code == 2)
		return ("Your host is " + arg1 + ", running version " + arg2);
	else if (code == 3)
		return ("This server was created " + arg1);
	else if (code == 4)
		return (arg1 + " " + arg2 + " " + arg3 + " " + arg4);
	else if (code == 251)
		return (":There are " + arg1 + " users and " + arg2);
	else if (code == 252)
		return (arg1 + " :operator(s) online");
	else if (code == 253)
		return (arg1 + " :unknown connection(s)");
	else if (code == 254)
		return (arg1 + " :channels formed");
	else if (code == 255)
		return (":I have " + arg1 + " clients and " + arg2 + " servers");
	else if (code == 372)
		return (":- " + arg1);
	else if (code == 375)
		return (":- " + arg1 + " Message of the day - ");
	else if (code == 376)
		return (":End of MOTD command");
	else if (code == 401)
		return (":No such nick/channel");
	else if (code == 431)
		return (":No nickname given");
	else if (code == 432)
		return (arg1 + " :Erroneus nickname");
	else if (code == 433)
		return (arg1 + " :Nickname is already in use");
	else if (code == 461)
		return (arg1 + " :Not enough parameters");
	else if (code == 462)
		return (":You may not reregister");
	else if (code == 464)
		return (":Password incorrect");
	else if (code == 402)
		return (arg1 + " :No such server");
	else if (code == 481)
		return (":Permission Denied- You're not an IRC operator");
	else if (code == 484)
		return (":Your connection is restricted!");
}
