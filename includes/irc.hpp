/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkodaira <kkodaira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 21:55:42 by akamite           #+#    #+#             */
/*   Updated: 2024/10/07 19:45:11 by kkodaira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_HPP
#define IRC_HPP

#include "Server.hpp"
#include "Config.hpp"
#include "Utils.hpp"
#include "User.hpp"
#include "Display.hpp"
#include "Command.hpp"
#include "Channel.hpp"

#include <iostream>
#include <csignal>
#include <algorithm>

#ifndef IS_MAC
#define IS_MAC true
#endif

extern bool stop;

#endif