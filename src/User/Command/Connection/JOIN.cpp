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

  if (channelName[0] != '#')
    return false;

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
    /** ユーザー追加 ⚪︎管理者 */
    channel.addUser(user, true);
  }
  else
  {
    /** TODO[kmt] すでにユーザーが入っている場合の処理 */
    channel.removeUserInvite(user);

    /** ユーザー追加 ×管理者 */
    channel.addUser(user, false);
  }

  irc::put_channels(server.getChannels());

  if (DEBUG)
    std::cout << "JOIN: " << user.getNickname() << " is joined to " << channel.getName() << std::endl;
  channel.broadcast(user, "JOIN :" + channel.getName());
  command->reply(user, 353, "*", channelName, "@DebugUser");
  command->reply(user, 366, channelName);
}
