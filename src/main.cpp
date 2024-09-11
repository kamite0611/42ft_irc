/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkodaira <kkodaira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 21:29:39 by akamite           #+#    #+#             */
/*   Updated: 2024/09/11 17:25:33 by kkodaira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cerr << "invalid argument count." << std::endl;
		return (1);
	}

	try
	{
		irc::Server	server;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return (1);
	}
	
	return 0;
}
