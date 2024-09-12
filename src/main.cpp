/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamite <akamite@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 21:29:39 by akamite           #+#    #+#             */
/*   Updated: 2024/09/12 23:58:36 by akamite          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

void handler(int signal)
{
	(void)signal;
	stop = true;
}

bool stop = false;

int main(int argc, char **argv)
{
	if (argc != 3)
		irc::printError("invalid argument count", true);

	irc::Server server;
	signal(SIGINT, handler);

	server.getConfig().set("port", argv[1]);
	server.getConfig().set("password", argv[2]);

	server.init();
	while (!stop)
	{
		server.execute();
	}
	return 0;
}
