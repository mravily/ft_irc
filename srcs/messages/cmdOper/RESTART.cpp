/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RESTART.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravily <mravily@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 09:31:00 by mravily           #+#    #+#             */
/*   Updated: 2022/07/20 09:31:22 by mravily          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void RESTART(irc::Server *srv, irc::User *usr, irc::Command *cmd)
{
	(void)cmd;
	if (usr->getStatus() == irc::REGISTERED || usr->getStatus() == irc::ONLINE)
	{
		if (usr->getOperator() == true)
			srv->setRestart(true);
		else
			usr->reply(481);
	}
}
