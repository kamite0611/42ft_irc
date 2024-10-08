#pragma once

#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string>
#include <map>
#include <algorithm>

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
        CAPLS,
        PASSWORD,
        REGISTER, /*Userが接続だけして名前などの登録を行っていない*/
        ONLINE,
        DELETE, /*削除*/
    };

    class User
    {
    private:
        std::map<std::string, void (*)(Command *)> _commandFunctions;
        int _fd;
        std::string _nickname;
        std::string _pastNickname;
        std::string _hostname;
        std::string _hostaddr;
        std::string _username;
        std::string _realname;
        std::string _mode;
        Server *_server;
        UserStatus _status;
        std::string _buffer;
        std::vector<Command *> _command;
        std::vector<std::string> _waitToSend;
        std::string _quitMessage;
        std::time_t _lastPingTime;

    public:
        User(int fd, Server *server, struct sockaddr_in address);
        ~User();

        /** Getters */
        std::string getNickname() const;
        UserStatus getStatus() const;
        std::string getPrefix() const;
        std::string getHost() const;
        std::string getMode() const;
        std::string getPastNickname() const;
        int getFd() const;
        std::string getQuitMessage() const;
		std::time_t getLastPingTime();


        /** Setters*/
        void setStatus(UserStatus status);
        void setPastNickname(const std::string& pastNickname);
        void setNickname(const std::string& nickname);
        void setUsername(const std::string& username);
        void setRealname(const std::string& realname);
        void setQuitMessage(const std::string& quitMessage);
        void setMode(bool isPlus, char mode);
        void setLastPingTime(std::time_t lastPingTime);

        /**  */
        void completeUserRegistration(Command *command);
        void dispatch(); /*Command識別*/
        void receive();  /*UserへのPOLLINイベント、コマンド作成*/

        /*メッセージ送信*/
        void write(const std::string &message);
        void sendTo(irc::User &recipient, const std::string &message, const std::string &delimiter = "");
        void push();
    };
}
