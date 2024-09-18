/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkodaira <kkodaira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 23:37:02 by akamite           #+#    #+#             */
/*   Updated: 2024/09/18 16:56:58 by kkodaira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
#define USER_HPP

#include <iostream>
#include <netinet/in.h>

namespace irc
{
    class Server;

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
    public:
        User(int fd, Server *server, struct sockaddr_in address);
        ~User();

        /** Getters */
        std::string getNickname() const;
        UserStatus getStatus() const;

        /**  */
        void receive(); /*UserへのPOLLINイベント*/

		/*メッセージ送信*/
		void push();
    };
}

#endif
