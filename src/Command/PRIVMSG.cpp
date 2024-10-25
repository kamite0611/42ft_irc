#include "irc.hpp"

/**
 * ユーザーにダイレクトメッセージする
 */
void sendToUser(irc::Command *command, std::string message)
{
  irc::User &user = command->getUser();
  std::vector<std::string> params = command->getParameter();
  std::string targetName = params[0];
  irc::Server &server = command->getServer();

  irc::User *targetUser = server.findUserByNickname(targetName);
  if (!targetUser)
    return command->reply(user, 404, targetName);

  user.sendTo(*targetUser, "PRIVMSG " + targetName + " :" + message);
}

/**
 * チャンネル内全員に向けメッセージを送信する
 */
void sendToChannel(irc::Command *command, std::string message)
{
  std::vector<std::string> params = command->getParameter();
  irc::User &user = command->getUser();
  std::string targetName = params[0];
  irc::Server &server = command->getServer();
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

/**
 * PRVMSG メッセージの送信
 */
void PRIVMSG(irc::Command *command)
{
  std::vector<std::string> params = command->getParameter();
  std::string targetName = params[0];
  irc::User &user = command->getUser();
  std::string message = command->getTrailer();

  if (!params.size() || !message.length())
    return command->reply(user, 461, "PRIVMSG");

  if (targetName[0] == '#')
    return sendToChannel(command, message);
  else
    return sendToUser(command, message);
}
