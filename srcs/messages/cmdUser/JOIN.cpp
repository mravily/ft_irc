/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravily <mravily@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 18:05:31 by mravily           #+#    #+#             */
/*   Updated: 2022/07/20 16:07:07 by nayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

bool chanExist(irc::Server *srv, std::string toFind)
{

	std::vector<irc::Channel *> Chan(srv->getChannels());
	std::vector<irc::Channel *>::iterator it(Chan.begin());
	for (; it != Chan.end(); it++)
	{
		std::cout << (*it)->getName() << std::endl;
		if (!toFind.compare((*it)->getName()))
			return (true);
	}
	return (false);
}

void JOIN(irc::Server *srv, irc::User *usr, irc::Command *cmd)
{
	if (usr->getStatus() == irc::REGISTERED || usr->getStatus() == irc::ONLINE)
	{
		if (cmd->getParams().empty())
		{
			usr->reply(461);
			return ;
		}
		std::vector<std::string> chanNames = split(cmd->getParams()[0], ",");
		std::vector<std::string>::iterator itNames(chanNames.begin());
		irc::Channel* chan = NULL;
		for (; itNames != chanNames.end(); itNames++)
		{
			if (itNames->find("#") == std::string::npos)
				itNames->insert(itNames->begin(), '#');
		}
		itNames = chanNames.begin();
		for (; itNames != chanNames.end(); itNames++)
		{
			if (!(chan = findChan(srv, (*itNames))))
				srv->createChan((*itNames), usr);
			else
				srv->joinChan(chan, usr);
		}
	}	
}
