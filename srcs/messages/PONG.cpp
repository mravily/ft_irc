// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   PONG.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jiglesia <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2022/07/22 14:06:12 by jiglesia          #+#    #+#             //
//   Updated: 2022/07/22 14:06:12 by jiglesia         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Server.hpp"

void PONG(irc::Server *srv, irc::User *usr, irc::Command *cmd)
{
	(void)srv;
	if (cmd->getTrailer().compare(usr->getNickname()) == 0)
	{
        std::cout << "DEBUG pong\n";
		usr->setLastPong();
		usr->setStatus(irc::ONLINE);
	}
}