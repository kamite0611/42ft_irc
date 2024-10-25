#include "irc.hpp"
#include <iostream>

/**
 * チャンネルへの参加可否をチェック
 * - 既存チャンネルのモードによる条件チェック
 *  1. チャンネルパスワード (k モード)
 *  2. ユーザー制限 (l モード)
 *  3. 招待制 (i モード)
 */
bool isValidJoin(irc::Command *command)
{
  std::vector<std::string> params = command->getParameter();
  irc::Server &server = command->getServer();
  irc::User &user = command->getUser();

  if (params.size() == 0)
    return command->reply(user, 461, "JOIN"), false;

  std::string channelName = params[0];
  std::string password = params.size() > 2 ? params[1] : std::string();

  if (channelName[0] != '#')
    return false;

  irc::Channel *channel = server.findChannel(channelName);
  if (!channel)
    return true; // 既存チャンネルがない場合OK

  /** パスワード */
  if (channel->getMode().find('k') != std::string::npos && channel->getPassword() != password)
    return command->reply(user, 475, channelName), false;

  /** ユーザー人数制限 */
  if (channel->getMode().find('l') != std::string::npos && channel->getUsers().size() >= (size_t)atoi(channel->getMaxUsers().c_str()))
    return command->reply(user, 471, channelName), false;

  /** 招待制 */
  if (channel->getMode().find('i') != std::string::npos && !channel->isInvitedUser(user))
    return command->reply(user, 473, channelName), false;

  return true;
}

/**
 * チャンネルへのユーザー追加と通知
 */
void JOIN(irc::Command *command)
{
  std::vector<std::string> params = command->getParameter();

  if (!isValidJoin(command))
    return;

  std::string channelName = params[0];
  irc::Server &server = command->getServer();
  irc::User &user = command->getUser();
  irc::Channel &channel = server.createOrFindChannel(channelName);

  if (channel.getUsers().size() == 0)
  {
    channel.addUser(user, true);
    user.setMode(true, 'o');
  }
  else
  {
    /** すでにユーザーが入っている場合の処理 */
    channel.removeUserInvite(user);
    channel.addUser(user, false);
  }

  if (DEBUG)
  {
    irc::put_channels(server.getChannels());
    std::cout << "JOIN: " << user.getNickname() << " is joined to " << channel.getName() << std::endl;
  }
  channel.broadcast(user, "JOIN :" + channel.getName());

  /** TODO [kamite] レスポンスメッセージ調整 */
  command->reply(user, 353, "*", channelName, channel.getUserNameString());
  command->reply(user, 366, channelName);
}
