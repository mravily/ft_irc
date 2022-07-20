/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   INVITE.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravily <mravily@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 09:32:19 by mravily           #+#    #+#             */
/*   Updated: 2022/07/20 09:32:31 by mravily          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"


void INVITE(irc::Server *srv, irc::User *usr, irc::Command *cmd)
{
	if (usr->getStatus() == irc::REGISTERED || usr->getStatus() == irc::ONLINE)
	{
		if (cmd->getParams().size() < 2)
		{
			usr->reply(461);
			return;
		}
		std::string nameTarget = cmd->getParams()[0];
		std::string nameChannel = cmd->getParams()[1];
		irc::User *target;
		irc::Channel *chan = findChan(srv, nameChannel);
		if (chan == NULL)
		{
			usr->reply(401); // devrait etre 403 NOSUCHCHANNEL
			return;
		}
		else if (chan->knowUser(usr) == false)
		{
			usr->reply(442);
			return;
		}
		else if ((target = srv->getUserByNick(nameTarget)) == NULL)
		{
			usr->reply(401);
			return;
		}
		else if (chan->knowUser(target) == true)
		{
			usr->reply(443, chan);
			return;
		}
		else if (chan->isOperator(usr) == false)
		{
			usr->reply(482, chan);
			return;
		}
		else
		{
			std::string response = ":" + usr->getClient() + " INVITE " + nameTarget + " " + nameChannel + CRLF;
			send(target->getFd(), response.c_str(), response.length(), 0);
			usr->addWaitingSend(":" + usr->getClient() + " 341 " + usr->getNickname() + " " + nameTarget + " :" + nameChannel + CRLF);
			if (target->haveInvitation(nameChannel) == false) //eviter doublon
				target->addInvitation(nameChannel);
		}
	}
}