/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kai11 <kai11@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 23:39:10 by akamite           #+#    #+#             */
/*   Updated: 2024/10/04 14:43:10 by kai11            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"
#include <iostream>
#include <arpa/inet.h>

/*
Command Functions
*/
void CAP(irc::Command* command);
void PASS(irc::Command* command);
void NICK(irc::Command* command);
void USER(irc::Command* command);

irc::User::User(int fd, Server *server, struct sockaddr_in address) : _fd(fd),
                                                                      _server(server),
                                                                      _status(REGISTER)
{
    (void)address;
    
}

irc::User::~User()
{
}

/*Getter*/
std::string irc::User::getNickname() const { return (_nickname); }
irc::UserStatus irc::User::getStatus() const { return (this->_status); }
std::string irc::User::getPrefix() const
{
    if (_status == CAPLS || _status == PASSWORD || _status == REGISTER)
        return (std::string(""));

    std::string prefix = _nickname;
    if (getHost().length())
    {
        if (_username.length())
            prefix += "!" + _username;
        prefix += "@" + getHost();
    }
    return (prefix);
}
std::string irc::User::getHost() const
{
    if (_hostname.length())
        return (_hostname);
    return (_hostaddr);
}
std::string irc::User::getMode() const { return (_mode); }
std::string irc::User::getPastNickname() const { return (_pastNickname); };
int irc::User::getFd() const { return (_fd); }

/*
Setters
*/
void irc::User::setStatus(UserStatus status) { _status = status; }
void irc::User::setPastNickname(const std::string& pastNickname) { _pastNickname = pastNickname; }
void irc::User::setNickname(const std::string& nickname) { _nickname = nickname; }

void irc::User::dispatch()
{
    if (_status == DELETE)
        return ;

    
    std::vector<Command*> used;
    for (std::vector<Command*>::iterator it = _command.begin(); it != _command.end(); it++)
    {
        if ((*it)->getUser().getStatus() == CAPLS && (*it)->getPrefix() != "CAP")
            continue ;
        if ((*it)->getUser().getStatus() == PASSWORD && (*it)->getPrefix() != "PASS")
            continue ;
        if ((*it)->getUser().getStatus() == REGISTER && ((*it)->getPrefix() != "NICK" || (*it)->getPrefix() != "USER"))
            continue ;
        /*TODO created by kkodaira
            コマンド実行*/
        used.push_back(*it);
    }

    for (std::vector<Command*>::iterator it = used.begin(); it != used.end(); it++)
    {
        if (std::find(_command.begin(), _command.end(), *it) != _command.end())
        {
            _command.erase(std::find(_command.begin(), _command.end(), *it));
            delete *it;
        }
    }
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
    std::cout << "=============\n" << buffer << std::endl;
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
    dispatch();
}

void irc::User::write(const std::string& message)
{
    _waitToSend.push_back(message);
}

void irc::User::sendTo(irc::User& recipient, const std::string& message, const std::string& delimiter)
{
    if (!delimiter.length())
        recipient.write(message);
    recipient.write(delimiter + this->getPrefix() + " " + message);
}

void irc::User::push()
{
    /**/
}