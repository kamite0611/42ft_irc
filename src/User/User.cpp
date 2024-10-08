#include "User.hpp"
#include <iostream>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

/*
Command Functions
*/
void CAP(irc::Command *command);
void PASS(irc::Command *command);
void NICK(irc::Command *command);
void USER(irc::Command *command);
void LUSERS(irc::Command *command);
void MOTD(irc::Command *command);
void QUIT(irc::Command* command);
void JOIN(irc::Command *command);
void MODE(irc::Command* command);
void PING(irc::Command* command);
void PONG(irc::Command* command);
void TOPIC(irc::Command* command);

irc::User::User(int fd, Server *server, struct sockaddr_in address) : _fd(fd),
                                                                      _server(server),
                                                                      _status(irc::CAPLS)
{
    fcntl(fd, F_SETFL, O_NONBLOCK);
    _hostaddr = inet_ntoa(address.sin_addr);
    char hostname[NI_MAXHOST];
    if (getnameinfo((struct sockaddr *)&address, sizeof(address), hostname, NI_MAXHOST, NULL, 0, NI_NUMERICSERV) != 0)
        printError("getnameinfo", true);
    else
        _hostname = hostname;

    _lastPingTime = std::time(0);
    _commandFunctions["CAP"] = CAP;
    _commandFunctions["PASS"] = PASS;
    _commandFunctions["NICK"] = NICK;
    _commandFunctions["USER"] = USER;
    _commandFunctions["QUIT"] = QUIT;
    _commandFunctions["JOIN"] = JOIN;
    _commandFunctions["MODE"] = MODE;
    _commandFunctions["PING"] = PING;
    _commandFunctions["PONG"] = PONG;
    _commandFunctions["TOPIC"] = TOPIC;
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
std::string irc::User::getQuitMessage() const 
{
    if (_quitMessage.length())
        return (_quitMessage);
    return ("Client Quit");
}
std::time_t irc::User::getLastPingTime() { return (_lastPingTime); }

/*
Setters
*/
void irc::User::setStatus(UserStatus status) { _status = status; }
void irc::User::setPastNickname(const std::string &pastNickname) { _pastNickname = pastNickname; }
void irc::User::setNickname(const std::string &nickname) { _nickname = nickname; }
void irc::User::setUsername(const std::string &username) { _username = username; }
void irc::User::setRealname(const std::string &realname) { _realname = realname; }
void irc::User::setQuitMessage(const std::string& quitMessage) { _quitMessage = quitMessage; }
void irc::User::setMode(bool isPlus, char mode)
{
    if (isPlus && _mode.find(mode) == std::string::npos)
        _mode += mode;
    else if (!isPlus && _mode.find(mode) != std::string::npos)
        _mode.erase(_mode.find(mode));
    if (DEBUG)
    {
        std::cout << _nickname << " now mode= " << _mode << std::endl;
    }
}
void irc::User::setLastPingTime(std::time_t lastPingTime) { _lastPingTime = lastPingTime; }


void irc::User::completeUserRegistration(Command *command)
{
    command->reply(*this, 1, getPrefix());
    command->reply(*this, 2, getHost(), _server->getConfig().get("version"));
    command->reply(*this, 3, _server->_getBootTime());
    command->reply(*this, 4, _server->getConfig().get("name"), _server->getConfig().get("version"),
                   _server->getConfig().get("user_mode"), _server->getConfig().get("channel_givemode"));

    LUSERS(command);
    MOTD(command);
}

void irc::User::dispatch()
{
    UserStatus lastStatus = _status;
    if (lastStatus == DELETE)
        return ;

    // if (DEBUG)
    // {
    //     std::cout << "now commands\n";
    //     for (std::vector<Command *>::iterator it = _command.begin(); it != _command.end(); it++)
    //         std::cout << (*it)->getPrefix() << std::endl;
    // }
    std::vector<Command *> used;
    for (std::vector<Command *>::iterator it = _command.begin(); it != _command.end(); it++)
    {
        if (lastStatus == CAPLS)
        {
            if ((*it)->getPrefix() != "CAP")
                continue;
        }
        else if (lastStatus == PASSWORD)
        {
            if ((*it)->getPrefix() != "PASS")
                continue;
        }
        else if (lastStatus == REGISTER)
        {
            if ((*it)->getPrefix() != "NICK" && (*it)->getPrefix() != "USER")
                continue;
        }
        if (_commandFunctions.count((*it)->getPrefix()))
            _commandFunctions[(*it)->getPrefix()]((*it));
        used.push_back(*it);
    }

    for (std::vector<Command *>::iterator it = used.begin(); it != used.end(); it++)
    {
        if (std::find(_command.begin(), _command.end(), *it) != _command.end())
        {
            _command.erase(std::find(_command.begin(), _command.end(), *it));
            delete *it;
        }
    }

    if (lastStatus == REGISTER)
    {
        if (_nickname.length() && _realname.length())
        {
            setStatus(ONLINE);
        }
    }

    if (lastStatus != _status)
    {
        if (_status == ONLINE)
        {
            Command *command = new Command(this, _server, "");
            completeUserRegistration(command);
            delete command;
        }
        dispatch();
    }
}

void irc::User::receive()
{
    {
        char buffer[BUFFER_SIZE + 1];
        ssize_t recv_bytes;

        if ((recv_bytes = recv(_fd, &buffer, BUFFER_SIZE, 0)) == -1) /*readでもいいかも*/
            irc::printError("recv", true);
        if (recv_bytes == 0)
        {
            _status = DELETE; /*POLLINが起きているのに読み取りがないので、相手が接続を正常終了した*/
            return;
        }
        buffer[recv_bytes] = 0;
        _buffer += buffer;
    }

    std::string delimiter(MESSAGE_END);
    size_t pos;
    while ((pos = _buffer.find(delimiter)) != std::string::npos)
    {
        std::string message =
            _buffer.substr(0, pos); /*messageには終端文字\r\nは含まない*/
        _buffer.erase(0, pos + delimiter.length());
        if (!message.length())
            continue;
        _command.push_back(new Command(this, _server, message));
    }
    dispatch();
}

void irc::User::write(const std::string &message)
{
    _waitToSend.push_back(message);
}

void irc::User::sendTo(irc::User &recipient, const std::string &message, const std::string &delimiter)
{
    if (!delimiter.length())
        recipient.write(message);
    recipient.write(delimiter + this->getPrefix() + " " + message);
}

void irc::User::push()
{
    if (!_waitToSend.size())
        return;

    std::string buffer;
    for (std::vector<std::string>::iterator it = _waitToSend.begin(); it != _waitToSend.end(); ++it)
    {
        buffer += *it + MESSAGE_END;
    }

    _waitToSend.clear();

    if (buffer.length())
        if (send(_fd, buffer.c_str(), buffer.length(), 0) == -1)
            printError("send", false);
}