/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravily <mravily@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 09:30:16 by mravily           #+#    #+#             */
/*   Updated: 2022/07/20 16:20:24 by nayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void KICK(irc::Server *srv, irc::User *usr, irc::Command *cmd)
{
	if (usr->getStatus() == irc::REGISTERED || usr->getStatus() == irc::ONLINE)
	{
		if (cmd->getParams().size() < 2)
		{
			usr->reply(461);
			return;
		}
		irc::Channel *chan;
		irc::User *target;
		std::string channelName = cmd->getParams()[0];
		std::vector<std::string> names = split(cmd->getParams()[1], ",");
		std::string reason = cmd->getTrailer();
		if (!reason.size())
			reason = "no reason";

		if ((chan = findChan(srv, channelName)) == NULL)
		{
			usr->reply(401, chan);
			return;
		}
		else if (chan->knowUser(usr) == false && usr->getOperator() == false)
		{
			usr->reply(442, chan);
			return;
		}

		for (std::vector<std::string>::iterator it = names.begin(); it != names.end(); it++)
		{
			if ((target = srv->getUserByNick(*it)) == NULL)
				usr->reply(403, chan);
			else if (chan->knowUser(target) == false)
				usr->reply(441, chan);
			else
			{
				if (chan->isOperator(usr) == false && usr->getOperator() == false)
					usr->reply(482, chan);
				else
				{
					chan->kickUser(usr, target, reason);
					if (chan->getUserSize() == "0")
						srv->removeChan(chan->getName());
				}
			}
		}
	}
}
