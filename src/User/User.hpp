/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kai11 <kai11@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 23:37:02 by akamite           #+#    #+#             */
/*   Updated: 2024/09/27 20:21:30 by kai11            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
#define USER_HPP

#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string>

#include "Utils.hpp"
#include "Command.hpp"

/*メッセージ1つあたりの最大長が512byteで、複数メッセージを処理するのに十分なサイズ*/
#define BUFFER_SIZE 4096
#define MESSAGE_END "\r\n"

namespace irc
{
    class Server;
    class Command;

    enum UserStatus
    {
        REGISTER, /*Userが接続だけして名前などの登録を行っていない*/
        DELETE, /*削除*/
    };

    class User
    {
    private:
        int _fd;
        std::string _nickname;
        Server *_server;
        UserStatus _status;
        std::string _buffer;
        std::vector<Command*> _command;
    public:
        User(int fd, Server *server, struct sockaddr_in address);
        ~User();

        /** Getters */
        std::string getNickname() const;
        UserStatus getStatus() const;

        /**  */

        void dispatch(); /*Command識別*/
        void receive(); /*UserへのPOLLINイベント、コマンド作成*/

		/*メッセージ送信*/
		void push();
    };
}

#endif
