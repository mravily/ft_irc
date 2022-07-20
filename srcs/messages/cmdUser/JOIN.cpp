/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.CPP                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravily <mravily@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 18:05:31 by mravily           #+#    #+#             */
/*   Updated: 2022/07/20 08:41:55 by mravily          ###   ########.fr       */
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
		std::vector<std::string> keys;
		std::vector<std::string>::iterator itPass;
		if (cmd->getParams().size() > 1)
		{
			std::vector<std::string> keys = split(cmd->getParams()[1], ",");
			itPass = keys.begin();
		}
		else
		{
			std::vector<std::string> chanNames = split(cmd->getParams()[0], ",");
			std::vector<std::string>::iterator itNames(chanNames.begin());
			irc::Channel* chan = NULL;
			for (; itNames != chanNames.end(); itNames++)
			{
				if (!(chan = findChan(srv, (*itNames))))
					srv->createChan((*itNames), usr);
				else
					srv->joinChan(chan, usr);
			}
		}
	}	
}
