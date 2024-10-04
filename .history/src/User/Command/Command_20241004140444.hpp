#ifndef COMMAND_HPP
# define COMMAND_HPP

#include "User.hpp"
#include "Server.hpp"

namespace irc
{
	class User;
	class Server;

	class Command
	{
	private:
		User*						_user;
		Server*						_server;
		std::string					_prefix;
		std::vector<std::string>	_parameters;
		std::string					_trailer;
		std::string					_query;
	public:
		Command(User* user, Server* server, std::string message);
		~Command();

		/*getters*/
		std::vector<std::string>& getParameter();
		irc::User& getUser();
		std::string getReplyMessage(int code, const std::string& arg1);
		irc::Server& getServer();
		std::string& getPrefix();

		/*optional*/
		void reply(User& user, int code, const std::string& arg1 = "");
	};
}

#endif