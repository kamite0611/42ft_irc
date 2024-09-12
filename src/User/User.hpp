/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamite <akamite@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 23:37:02 by akamite           #+#    #+#             */
/*   Updated: 2024/09/13 00:34:10 by akamite          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
#define USER_HPP

#include <iostream>

namespace irc
{
    class Server;

    class User
    {
    private:
        int fd;
        std::string nickname;
        Server *server;

    public:
        User(int fd, Server *server, struct sockaddr_in address);
        ~User();

        /** Getters */
        std::string getNickname() const;
    };
}

#endif
