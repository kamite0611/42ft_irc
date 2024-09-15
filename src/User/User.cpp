/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamite <akamite@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 23:39:10 by akamite           #+#    #+#             */
/*   Updated: 2024/09/14 18:16:15 by akamite          ###   ########.fr       */
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
