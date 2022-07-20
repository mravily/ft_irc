/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NAMES.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravily <mravily@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 09:33:01 by mravily           #+#    #+#             */
/*   Updated: 2022/07/20 09:33:10 by mravily          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void NAMES(irc::Server *srv, irc::User *usr, irc::Command *cmd)
{
	if (usr->getStatus() == irc::REGISTERED || usr->getStatus() == irc::ONLINE)
	{
		std::vector<std::string> channelNames = cmd->getParams();

		irc::Channel *chan;
		for (std::vector<std::string>::iterator it = channelNames.begin(); it != channelNames.end(); it++)
		{
			if ((chan = findChan(srv, *it)) != NULL)
			{
				usr->reply(353, chan);
				usr->reply(366, chan);
			}
			else
				usr->reply(401);
		}
	}
}
