/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QUIT.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravily <mravily@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 08:32:55 by mravily           #+#    #+#             */
/*   Updated: 2022/07/20 08:33:11 by mravily          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void QUIT(irc::Server *srv, irc::User *usr, irc::Command *cmd)
{
	if (cmd->getParams().empty())
		cmd->setTrailer("Leaving");
	usr->setReason(cmd->getTrailer());
	usr->setStatus(irc::LEAVE);
	srv->broadcast(" QUIT :" + usr->getReason());
}