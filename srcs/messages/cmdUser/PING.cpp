/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PING.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravily <mravily@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 18:37:24 by mravily           #+#    #+#             */
/*   Updated: 2022/07/20 08:43:28 by mravily          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void PING(irc::Server *srv, irc::User *usr, irc::Command *cmd)
{
	(void)srv;
	if (usr->getStatus() == irc::REGISTERED || usr->getStatus() == irc::ONLINE)
	{
		if (!cmd->getParams().size())
		{
			usr->reply(461);
			return ;
		}
		usr->addWaitingSend(":" + usr->getNickname() + "!" + usr->getUsername() + "@" + usr->getHostname() + " " + "PONG :" + cmd->getParams()[0] + CRLF);
		usr->setStatus(irc::ONLINE);
	}
}
