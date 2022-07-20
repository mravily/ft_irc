/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OPER.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravily <mravily@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 09:19:17 by mravily           #+#    #+#             */
/*   Updated: 2022/07/20 09:22:17 by mravily          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void OPER(irc::Server *srv, irc::User *usr, irc::Command *cmd)
{
	if (usr->getStatus() == irc::REGISTERED || usr->getStatus() == irc::ONLINE)
	{
		if (cmd->getParams().size() != 2)
			usr->reply(461);		// ERR_NEEDMOREPARAMS
		else if (!srv->getOperName().compare(cmd->getParams()[0]) && !srv->getOperPassword().compare(cmd->getParams()[1]))
		{
			usr->setOper(true);
			usr->reply(381);		// RPL_YOUROPER
		}
		else
			usr->reply(464);		// ERR_PASSWDMISMATCH
	}
}