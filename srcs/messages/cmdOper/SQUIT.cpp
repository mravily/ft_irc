/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SQUIT.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravily <mravily@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 09:29:25 by mravily           #+#    #+#             */
/*   Updated: 2022/07/20 09:29:39 by mravily          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void SQUIT(irc::Server *srv, irc::User *usr, irc::Command *cmd)
{
	(void)srv;
	if (usr->getStatus() == irc::REGISTERED || usr->getStatus() == irc::ONLINE)
	{
		if (cmd->getParams().size() < 2)
			usr->reply(461);
		else if (usr->getOperator() == true)
		{
			//verify oper master
			std::string server = cmd->getParams()[0];
			if (!server.compare("localhost") || !server.compare("127.0.0.1") || !server.compare("::1"))
				srv->turnOff();
			else
				usr->reply(402);
		}
		else
			usr->reply(481);
	}
}