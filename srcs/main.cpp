/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doublevv <vv>                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 07:56:24 by doublevv          #+#    #+#             */
/*   Updated: 2025/08/09 12:09:52 by doublevv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../include/ClientServer.hpp"
#include "../include/Server.hpp"


int	main(int ac, char **av)
{
	Server	server;

	// if (ac != 3)
	// {
	// 	std::cout << "must have 2 arguments : a port number and a password" << std::endl;
	// 	return (1);
	// }
	//* parsing du password et du port
	try
	{
		server.checkPoll();
	}
	catch (const std::exception& e)
	{

	}
	return (0);
}

// int	main(int ac, char **av)
// {
// 	Server	server;

// 	// if (ac != 3)
// 	// {
// 	// 	std::cout << "must have 2 arguments : a port number and a password" << std::endl;
// 	// 	return (1);
// 	// }
// 	//* parsing du password et du port
// 	try
// 	{
// 		server.init_server();
// 		server.checkPoll();
// 	}
// 	catch (const std::exception& e)
// 	{

// 	}
// 	return (0);
// }
