/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkodaira <kkodaira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 23:39:10 by akamite           #+#    #+#             */
/*   Updated: 2024/09/18 16:59:14 by kkodaira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"
#include <iostream>
#include <arpa/inet.h>

irc::User::User(int fd, Server *server, struct sockaddr_in address) : _fd(fd),
                                                                      _server(server)
{
    (void)address;
}

irc::User::~User()
{
}

/*Getter*/
irc::UserStatus irc::User::getStatus() const { return (this->_status); }

void irc::User::receive()
{
    /* TODO[kkodaira] add */
}

void irc::User::push()
{
    /**/
}