/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRIVMSG.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravily <mravily@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 08:55:20 by mravily           #+#    #+#             */
/*   Updated: 2022/07/20 08:55:32 by mravily          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void PRIVMSG(irc::Server *srv, irc::User *usr, irc::Command *cmd)
{
	if (usr->getStatus() == irc::REGISTERED || usr->getStatus() == irc::ONLINE)
	{
		if (!cmd->getParams().size())
		{
			usr->reply(461);
			return ;
		}
		std::string msg = cmd->getTrailer();
		if (!msg.size())
		{
			usr->reply(412);
			return;
		}

		std::vector<std::string> Targets = split(cmd->getParams()[0], ",");
		irc::Channel* chan;
		irc::User* userTarget;
		// si arg n'est pas channel, go msg prive to user
		for (std::vector<std::string>::iterator it = Targets.begin(); it != Targets.end(); it++)
		{
			if ((chan = findChan(srv, (*it))) != NULL) // si channel diffusion message dans le channel
			{
				//si usr n'est pas dans le channel et que le chan est mode +n et qu'il n'est pas ops
				if (chan->knowUser(usr) == false && chan->findMode("n") == true && usr->getOperator() == false)
					usr->reply(404, chan);
				else
					usr->broadcast(chan, ":" + usr->getClient() + " " + cmd->getPrefix() + " " + (*it) + " :" + msg + CRLF, usr);
			}
			else // sinon msg prive to user
			{
				userTarget = srv->getUserByNick(*it);
				if (userTarget != NULL)
				{
					userTarget->addWaitingSend(":" + usr->getClient() + " " + cmd->getPrefix() + " " + (*it) + " :" + msg + CRLF);
				}
				else
					usr->reply(401);
			}
		}
	}
}
