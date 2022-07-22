/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TOPIC.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravily <mravily@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 09:01:00 by mravily           #+#    #+#             */
/*   Updated: 2022/07/22 17:50:05 by nayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"


void TOPIC(irc::Server *srv, irc::User *usr, irc::Command *cmd)
{
	if (usr->getStatus() == irc::REGISTERED || usr->getStatus() == irc::ONLINE)
	{
		if (!cmd->getParams().size())
		{
			usr->reply(461); // ERR NEED PARAM
			return;
		}
		
		irc::Channel *chan;
		
		if ((chan = findChan(srv, cmd->getParams()[0])) == NULL)
		{
			usr->reply(401); // no such chan(must be 403 !!)
			return;
		}
		
		if (!cmd->getTrailer().size() && cmd->getUnset() == false)
		{
			if (chan->getTopic() == "")
				usr->reply(331, chan);
			else
			{
				usr->reply(332, chan);
				usr->reply(333, chan);
			}
			return;
		}

		if (chan->knowUser(usr) == false && usr->getOperator() == false) // si user pas present dans channel
			usr->reply(442, chan);
		else if (chan->findMode("t") == true && chan->isOperator(usr) == false && usr->getOperator() == false) // si channel mode +t et no operator
			usr->reply(482, chan);
		else
		{
			std::string newTopic = cmd->getTrailer();
			
			if (cmd->getUnset() == true)
				chan->unsetTopic();
			else
				chan->setTopic(newTopic, usr->getNickname());
			std::string response = usr->getClient() + " TOPIC " + chan->getName() + " :" + chan->getTopic() + CRLF;
			usr->broadcast(chan, response, 0);
		}
	}
}
