/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KILL.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravily <mravily@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 09:18:17 by mravily           #+#    #+#             */
/*   Updated: 2022/07/20 09:18:27 by mravily          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void KILL(irc::Server *srv, irc::User *usr, irc::Command *cmd)
{
	if (usr->getStatus() == irc::REGISTERED || usr->getStatus() == irc::ONLINE)
	{
		irc::User* user = NULL;
		if (!cmd->getParams().size() || !cmd->getTrailer().size())
			usr->reply(461); // ERR_NEEDMOREPARAMS
		else if (!usr->getOperator())
			usr->reply(481); // ERR_NOPRIVILEGES
		else if (!(user = findUserSrv(srv, cmd->getParams()[0])))
			usr->reply(401); // ERR_NOSUCKNICK
		else
		{
			user->setStatus(irc::LEAVE);
			user->setReason(" Killed (" + usr->getNickname() + " " + cmd->getTrailer() + ")");
			srv->broadcast(" Killed (" + usr->getNickname() + " " + cmd->getTrailer() + ")");
			user->addWaitingSend(":" + user->getClient() + " ERROR: Closing link: IRC Hobbs Killed (" + usr->getNickname() + " " + cmd->getParams()[1] + ")" + CRLF);
		}
	}
}
