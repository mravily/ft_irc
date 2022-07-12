/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravily <mravily@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 14:50:12 by mravily           #+#    #+#             */
/*   Updated: 2022/07/10 20:10:36 by mravily          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

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