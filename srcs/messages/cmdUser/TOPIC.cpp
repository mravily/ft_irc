/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TOPIC.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravily <mravily@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 09:01:00 by mravily           #+#    #+#             */
/*   Updated: 2022/07/20 16:24:02 by nayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"


void TOPIC(irc::Server *srv, irc::User *usr, irc::Command *cmd)
{
	if (usr->getStatus() == irc::REGISTERED || usr->getStatus() == irc::ONLINE)
	{
		irc::Channel *chan;

		if ((chan = findChan(srv, cmd->getParams()[0])) == NULL)
		{
			usr->reply(401); // no such chan(must be 403 !!)
			return;
		}

		std::string newTopic = cmd->getTrailer();

		if (!newTopic.size())
			usr->reply(331, chan);
		else
		{
			if (chan->knowUser(usr) == false && usr->getOperator() == false) // si user pas present dans channel
				usr->reply(442, chan);
			else if (chan->findMode("t") == true && chan->isOperator(usr) == false && usr->getOperator() == false) // si channel mode +t et no operator
				usr->reply(482, chan);
			else
			{
				chan->setTopic(newTopic);
				std::string response = usr->getReplies(332, chan);
				usr->broadcast(chan, response, 0);
			}
		}
	}
}
