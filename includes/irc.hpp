#ifndef IRC_HPP
#define IRC_HPP

#include "Server.hpp"
#include "Config.hpp"
#include "Utils.hpp"
#include "User.hpp"
#include "Command.hpp"
#include "Channel.hpp"

#include <iostream>
#include <csignal>
#include <algorithm>
#include <string>

#ifndef IS_MAC
#define IS_MAC false
#endif

extern bool stop;

#endif