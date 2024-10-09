#include "irc.hpp"
#include <iostream>

/**
 *
 */
void KICK(irc::Command *command)
{
  std::vector<std::string> params = command->getParameter();
  irc::User &user = command->getUser();
  irc::Server &server = command->getServer();

  if (params.size() < 2)
    return command->reply(user, 461, "KICK");

  std::string channelName = params[0];
  std::string userName = params[1];

  if (!channelName.length() || !userName.length())
    return command->reply(user, 461, "KICK");

  irc::Channel *channel = server.findChannel(channelName);
  if (!channel)
    return command->reply(user, 403, channelName);

  irc::User *targetUser = channel->findUserByNickname(userName);

  if (!targetUser)
    return command->reply(user, 441, userName, channelName);

  channel->broadcast(user, "KICK " + channelName + " " + userName + ": " + params[2]);
  targetUser->write("Quit: " + targetUser->getQuitMessage());
  channel->delUser(*targetUser);
}
