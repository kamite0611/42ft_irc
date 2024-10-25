#include "irc.hpp"

/**
 * チャンネル内全員に向けメッセージを送信する
 */
void PRIVMSG(irc::Command *command)
{
  std::vector<std::string> params = command->getParameter();
  irc::User &user = command->getUser();
  std::string message = command->getTrailer();

  if (!params.size() || !message.length())
    return command->reply(user, 461, "PRIVMSG");

  irc::Server &server = command->getServer();
  std::string targetName = params[0];

  irc::Channel *channel = server.findChannel(targetName);
  if (!channel)
    return command->reply(user, 404, targetName);

  if (channel->getMode().find('n') != std::string::npos && !channel->isUser(user))
    return command->reply(user, 404, channel->getName());

  std::vector<irc::User *> users = channel->getUsers();
  for (std::vector<irc::User *>::iterator it = users.begin(); it != users.end(); it++)
  {
    std::cout << "User->" << (*it)->getNickname() << std::endl;
    if ((*it)->getFd() != user.getFd())
      user.sendTo(*(*it), "PRIVMSG " + channel->getName() + " :" + message);
  }
}
