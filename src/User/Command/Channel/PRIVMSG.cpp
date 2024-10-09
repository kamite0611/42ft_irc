#include "irc.hpp"

/**
 *
 */
void PRIVMSG(irc::Command *command)
{
  std::cout << std::endl
            << "hello PRIVMSG!" << std::endl;

  std::vector<std::string> params = command->getParameter();
  irc::Server &server = command->getServer();
  irc::User &user = command->getUser();
  std::string targetName = params[0];

  irc::Channel *channel = server.findChannel(targetName);
  if (!channel)
    return command->reply(user, 404, targetName);

  std::string message = command->getTrailer();
  std::vector<irc::User *> users = channel->getUsers();
  for (std::vector<irc::User *>::iterator it = users.begin(); it != users.end(); it++)
  {
    if ((*it)->getFd() != user.getFd())
      user.sendTo(*(*it), "PRIVMSG " + channel->getName() + " :" + message);
  }
}
