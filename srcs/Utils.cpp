/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravily <mravily@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 15:48:17 by mravily           #+#    #+#             */
/*   Updated: 2022/07/15 15:50:11 by mravily          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

irc::User* findUser(irc::Server *srv, std::string toFind)
{
	// std::cout << "FindUser->toFind: " << toFind << std::endl;
	std::map<int, irc::User *> Users(srv->getUsers());
	std::map<int, irc::User *>::iterator it(Users.begin());
	for (; it != Users.end(); it++)
	{
		std::cout << (*it).second->getNickname() << std::endl;
		if (!toFind.compare((*it).second->getNickname()))
			return ((*it).second);
	}
	return (NULL);
}

irc::Channel* findChan(irc::Server *srv, std::string toFind)
{
	std::cout << "FindUser->toFind: " << toFind << std::endl;
	std::vector<irc::Channel *> Chan(srv->getChannels());
	std::vector<irc::Channel *>::iterator it(Chan.begin());
	for (; it != Chan.end(); it++)
	{
		std::cout << (*it)->getName() << std::endl;
		if (!toFind.compare((*it)->getName()))
			return (*it);
	}
	return (nullptr);
}