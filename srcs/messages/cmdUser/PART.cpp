/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PART.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravily <mravily@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 07:46:59 by mravily           #+#    #+#             */
/*   Updated: 2022/07/20 08:42:53 by mravily          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

/* @brief Recherche dans les channels existant et quitte le channel avec une reason
** @param channel list des channels à quitter
** @param reason Raison pour la quel l'user quitte le channel
*/
void PART(irc::Server *srv, irc::User *usr, irc::Command *cmd)
{
	if (usr->getStatus() == irc::REGISTERED || usr->getStatus() == irc::ONLINE)
	{
		if (cmd->getParams().empty())
		{
			usr->reply(461);
			return ;
		}

		irc::Channel* chan = NULL;
		std::vector<std::string> chanNames = split(cmd->getParams()[0], ",");
		std::vector<std::string>::iterator itNames(chanNames.begin());
		for (; itNames != chanNames.end(); itNames++)
		{
			if (!(chan = findChan(srv, (*itNames))))
			{
				irc::Channel tmp(false, (*itNames), usr);
				usr->reply(403, &tmp);   // ERR_NOSUCHCHANNEL
			}
			else
			{
				chan->removeUser(usr, (" PART :" + chan->getName()));
				if (chan->getUserSize() == "0")
					srv->removeChan(chan->getName());
			}
		}
	}
}
