/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravily <mravily@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 14:50:12 by mravily           #+#    #+#             */
/*   Updated: 2022/07/06 13:34:50 by mravily          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

#include <sys/types.h> /* Voir NOTES */
#include <sys/socket.h>

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/socket.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
	   
#include <sys/types.h>
#include <sys/param.h>
#include <sys/socket.h> /* constantes, familles... */
#include <netinet/in.h> /* struct sockaddr_in */
#include <arpa/inet.h>  /* prototypes pour les fonctions dans inet(3N) */
#include <netdb.h>      /* struct hostent */
#include <poll.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#include <iostream>
#include <string>

// #include "server.hpp"
#include <vector>



std::vector<std::string> split(std::string s, std::string delimiter)
{
	std::vector<std::string> subString;

	size_t pos = 0;
	std::string token;
	while ((pos = s.find(delimiter)) != std::string::npos) 
	{
		token = s.substr(0, pos);
		subString.push_back(token);
		s.erase(0, pos + delimiter.length());
	}
	subString.push_back(s);
	return (subString);
}

bool checkArgs(int ac, char *port)
{
	if (ac != 3)
	{
		std::cout << "Error: Args provides isn't not well formatted\n"
		<< "./irc [port] [password]" << std::endl;
		return (false);
	}
	
	int i = 0;
	while (port[i])
	{
		if (std::isdigit(port[i]) == 0)
		{
			std::cout << "Error: Port not a number\n"
			<< "Provide a port between 0 - 65535" << std::endl;
			return (false);
		}
		i++;
	}
	int tmp = atoi(port);
	if (tmp < 0 || tmp > 65535)
	{
		std::cout << "Error: Port not a number\n"
		<< "Provide a port between 0 - 65535" << std::endl;
		return (false);
	}
	return (true);
}

int main(int ac, char **av)
{
	if (!checkArgs(ac, av[1]))
		return (1);

	irc::Server Server(av[1], av[2]);
	
	while (1)
		Server.runtime();
	return (0);
}