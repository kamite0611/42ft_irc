#include "irc.hpp"
#include <iostream>

/**
 * チャンネルへの参加可否をチェック
 * - チャンネル名が有効かどうか
 * - チャンネルの存在チェックおよび作成
 * - 既存チャンネルのモードによる条件チェック
 *  1. チャンネルパスワード (k モード)
 *  2. ユーザー制限 (l モード)
 *  3. 招待制 (i モード)
 */
void isValidJoin(irc::Command *command)
{
}

/**
 * チャンネルへのユーザー追加と通知
 */
void JOIN(irc::Command *command)
{
  std::vector<std::string> params = command->getParameter();

  if (params.size() != 1)
    return;

  std::string channelName = params[0];
  if (channelName[0] != '#')
    return; /** TODO error */

  irc::Server &server = command->getServer();
  irc::User &user = command->getUser();
  irc::Channel &channel = server.createOrFindChannel(channelName);

  if (channel.getUsers().size() == 0)
  {
    channel.addUser(user);
    /** TODO[kmt] setUserMode */
  }
  else
  {
    /** TODO[kmt] すでにユーザーが入っている場合の処理 */
  }

  irc::put_channels(server.getChannels());

  std::cout << "params[0]: " << params[0] << std::endl;
  std::cout << "Hello join!" << std::endl;
  std::cout << "parameters: " << command->getParameter().size() << std::endl;

  /** TODO 全てのユーザーにチャンネルに入ったことを通知 */

  command->reply(user, 366, channelName);
}
