/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kai11 <kai11@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 23:39:10 by akamite           #+#    #+#             */
/*   Updated: 2024/09/27 17:23:50 by kai11            ###   ########.fr       */
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

void irc::User::dispatch()
{
    /* TODO[kkodaira] add */
}

void irc::User::receive()
{
    char    buffer[BUFFER_SIZE + 1];
    ssize_t recv_bytes;

    if ((recv_bytes = recv(_fd, buffer, BUFFER_SIZE, 0)) == -1) /*readでもいいかも*/
        irc::printError("recv", true);
    if (recv_bytes == 0)
        _status = DELETE; /*POLLINが起きているのに読み取りがないので、相手が接続を正常終了した*/
    buffer[recv_bytes] = '\0';
    _buffer += buffer;

    std::string delimiter(MESSAGE_END);
    size_t  pos;
    while ((pos = _buffer.find(delimiter)) != std::string::npos)
    {
        std::string message = \
        _buffer.substr(0, pos); /*messageには終端文字\r\nは含まない*/
        _buffer.erase(0, pos + delimiter.length());
        if (message.length() == 0)
            continue ;
        _command.push_back(new Command(this, _server, message));
    }
    // dispatch();
}

void irc::User::push()
{
    /**/
}