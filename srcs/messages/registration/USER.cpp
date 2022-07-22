/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   USER.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravily <mravily@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 13:22:12 by mravily           #+#    #+#             */
/*   Updated: 2022/07/19 13:24:44 by mravily          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void USER(irc::Server *srv, irc::User *usr, irc::Command *cmd)
{
	if (cmd->getParams().size() < 3
		|| cmd->getParams()[0].size() == 1
		|| !cmd->getTrailer().size())
		usr->reply(461);
	else if (usr->getStatus() == irc::REGISTERED)
		usr->reply(462);
	else
	{
		usr->setBits(2);
		usr->setUsername(cmd->getParams()[0]);
		usr->setRealname(cmd->getTrailer());
	}
	(void)srv;
}