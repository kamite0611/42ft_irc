/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamite <akamite@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 23:37:02 by akamite           #+#    #+#             */
/*   Updated: 2024/09/14 18:16:05 by akamite          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
#define USER_HPP

#include <iostream>
#include <netinet/in.h>

namespace irc
{
    class Server;

    class User
    {
    private:
        int _fd;
        std::string _nickname;
        Server *_server;

    public:
        User(int fd, Server *server, struct sockaddr_in address);
        ~User();

        /** Getters */
        std::string getNickname() const;

        /**  */
    };
}

#endif
