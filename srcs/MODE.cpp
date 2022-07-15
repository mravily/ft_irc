/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MODE.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravily <mravily@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 15:47:22 by mravily           #+#    #+#             */
/*   Updated: 2022/07/15 18:33:18 by mravily          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

/*
** Vérifie si la modestring contient uniquement des modes
** autorisés apr le server
*/
bool checkUsrMode(std::string allowMode, std::string toCheck)
{
	std::string::iterator it(toCheck.begin());
	for (; it != toCheck.end(); it++)
	{
		if ((*it) == '-' || (*it) == '+')
			continue;
		if (allowMode.find((*it)) == std::string::npos)
			return (false);
	}
	return (true);
}

/*
** @brief Affiche les modes de l'utilisateur courant 
** si il existe et prépare la réponse correspondante
*/
void displayMode(irc::Server* srv, irc::User* usr, irc::Command* cmd)
{
	irc::User* user = nullptr;
	user = findUser(srv, cmd->getParams()[0]);

	if (user != usr)
		usr->reply(502);  		// ERR_USERSDONTMATCH
	else if (!user)
		usr->reply(401);   		// ERR_NOSUCHNICK 
	else
		usr->reply(221);  		// RPL_UMODEIS
}

void changeModeUser(irc::Server* srv, irc::User* usr, irc::Command* cmd)
{
	irc::User* user = nullptr;
	user = findUser(srv, cmd->getParams()[0]);
	if (user != usr)
		usr->reply(502);  		// ERR_USERSDONTMATCH
	else if (!user)
		usr->reply(401);   		// ERR_NOSUCHNICK 
	else if (!checkUsrMode(srv->getUsrMode(), cmd->getParams()[1]))
		user->reply(501);		// ERR_UMODEUNKNOWNFLAG
	else
	{
		std::cout << "cmd->getParams()[1]: " << cmd->getParams()[1] << std::endl;
		user->setMode(cmd->getParams()[1]);
	}
}

// Response: :kenny.chatspike.net 481 sasso :Permission Denied - Only operators may set user mode o
//     Prefix: kenny.chatspike.net
//     Command: 481
//     Command parameters
//         Parameter: sasso


void userMode(irc::Server *srv, irc::User *usr, irc::Command *cmd)
{	
	if (!cmd->getParams().size())
		usr->reply(461);
	if (cmd->getParams().size() == 1)
		displayMode(srv, usr, cmd);
	else
		changeModeUser(srv, usr, cmd);
}

void chanMode(irc::Server *srv, irc::User *usr, irc::Command *cmd)
{
	irc::Channel* chan = nullptr;
	chan = findChan(srv, cmd->getParams()[0]);
	if (!chan)
		usr->reply(403);
	else if (cmd->getParams().size() == 1)
	{
		usr->reply(324, chan);
		usr->reply(329, chan);
	}
	// else
	// {
	// 	if (!checkUsrMode(srv->getUsrMode(), cmd->getParams()[1]))
	// 		user->reply(501);
	// 	user->setMode(cmd->getParams()[1]);
	// }

}

void MODE(irc::Server *srv, irc::User *usr, irc::Command *cmd)
{
	if (!cmd->getParams().size())
		usr->reply(461);
	if (cmd->getParams()[0].find("#") != std::string::npos)
		chanMode(srv, usr, cmd);
	else
		userMode(srv, usr, cmd);
}
