/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LIST.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravily <mravily@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 08:59:08 by mravily           #+#    #+#             */
/*   Updated: 2022/07/20 08:59:20 by mravily          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void LIST(irc::Server *srv, irc::User *usr, irc::Command *cmd)
{
	(void)cmd;
	if (usr->getStatus() == irc::REGISTERED || usr->getStatus() == irc::ONLINE)
	{
		usr->reply(321);

		std::vector<irc::Channel *> channels; // va devenir la list des channels a afficher

		if (!cmd->getParams().empty() && !cmd->getParams()[0].empty()) // si il y a arguments (LIST <channel>,<channel>...)
		{
			std::vector<std::string> channelNames = split(cmd->getParams()[0], ",");
			channels = srv->getListChannelByName(channelNames);
		}
		else
			channels = srv->getChannels();

		for (std::vector<irc::Channel *>::iterator it = channels.begin(); it != channels.end(); it++)
		{
			if ((*it)->isPrivate() == false || (*it)->knowUser(usr) == true) // si channel prive (&) affiche seulement si user dedans
				usr->reply(322, (*it));
		}
		usr->reply(323);
	}
}