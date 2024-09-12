/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamite <akamite@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 23:39:10 by akamite           #+#    #+#             */
/*   Updated: 2024/09/13 00:36:07 by akamite          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"
#include <iostream>
#include <arpa/inet.h>

irc::User::User(int fd, Server *server, struct sockaddr_in address) : fd(fd),
                                                                      server(server)
{
    (void)address;
}

irc::User::~User()
{
}
