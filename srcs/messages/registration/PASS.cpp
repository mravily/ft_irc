/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASS.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravily <mravily@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 12:03:52 by mravily           #+#    #+#             */
/*   Updated: 2022/07/19 12:04:27 by mravily          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void PASS(irc::Server *srv, irc::User *usr, irc::Command *cmd)
{
	if (!cmd->getParams().size())
		usr->reply(461);    	// ERR_NEEDMOREPARAMS
	else if (usr->getStatus() == irc::CONNECTED && !cmd->getParams()[0].compare(srv->getPassword()))
	{
		usr->setStatus(irc::AUTHENTICATED);
		usr->setBits(0);
	}
	else if (usr->getStatus() != irc::CONNECTED && usr->getStatus() != irc::LEAVE)
		usr->reply(462);		// ERR_ALREADYREGISTERED
	else
		usr->reply(464);		// ERR_PASSWDMISMATCH
}