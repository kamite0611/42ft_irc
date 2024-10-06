#include "irc.hpp"
#include <iostream>

/**
 * チャンネルへの参加可否をチェック
 * - チャンネル名が有効かどうか
 * - チャンネルの存在チェックおよび作成
 */
void isValidJoin(irc::Command *command)
{
}

/**
 *
 */
void JOIN(irc::Command *command)
{
  std::vector<std::string> params = command->getParameter();

  if (params.size() != 1)
    return;

  std::string channelName = params[0];
  if (channelName[0] != '#')
    return; /** TODO error */

  irc::Server server = command->getServer();

  command->getServer().createOrFindChannel(channelName);

  // put_channels(server.getChannels());

  std::cout << "params[0]: " << params[0] << std::endl;
  std::cout << "Hello join!" << std::endl;
  std::cout << "parameters: " << command->getParameter().size() << std::endl;
}
