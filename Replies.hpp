/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Replies.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravily <mravily@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 21:25:38 by mravily           #+#    #+#             */
/*   Updated: 2022/07/04 21:56:34 by mravily          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLIES_HPP
#define REPLIES_HPP

#include "Server.hpp"
#include "User.hpp"

/*
** Réponses minimum à renvoyer lors d'une connexion au server
*/
std::string RPL_WELCOME(irc::Server *srv, irc::User usr) {return (":Welcome to the IRC Hobbs Network, " + usr.getNickname() + "!" + usr.getUsername() + "@" + usr.getHostname()); (void)srv;}
std::string RPL_YOURHOST(irc::Server *srv, irc::User usr) {return (":Your Host is " + usr.getHostname() + ", running version " + srv->getVersion());}
std::string RPL_CREATED(irc::Server *srv, irc::User usr) {return (":This server was created " + srv->getDatatime() + ""); (void)usr;}
std::string RPL_MYINFO(irc::Server *srv, irc::User usr) {return (usr.getHostname() + " IRCHobbs-" + srv->getVersion() + " " + srv->getUsrMode() + " " + srv->getChanMode() + " :FIJLXabefghjkloqv");};
std::string RPL_UMODEIS(irc::Server *srv, irc::User usr) {return (usr.getMode()); (void)srv;};

/* MODE Replies 401 502 501*/
std::string ERR_NOSUCHNICK(irc::Server *srv, irc::User usr) {return (":No such nick/channel"); (void)srv; (void)usr;};
std::string ERR_USERSDONTMATCH(irc::Server *srv, irc::User usr) {return (":Cant change mode for other users"); (void)srv; (void)usr;};
std::string ERR_UMODEUNKNOWNFLAG(irc::Server *srv, irc::User usr) {return (":Unknown MODE flag"); (void)srv; (void)usr;};

/* PASS Replies 461 462 464 */
std::string ERR_NEEDMOREPARAMS(irc::Server *srv, irc::User usr) {return (":Not enough parameters"); (void)srv; (void)usr;};
std::string ERR_ALREADYREGISTERED(irc::Server *srv, irc::User usr) {return (":You may not reregister"); (void)srv; (void)usr;};
std::string ERR_PASSWDMISMATCH(irc::Server *srv, irc::User usr) {return (":Password incorrect"); (void)srv; (void)usr;};

/* NICK Replies 431 432 433 */
std::string ERR_NONICKNAMEGIVEN(irc::Server *srv, irc::User usr) {return (":No nickname given"); (void)srv; (void)usr;};
std::string ERR_ERRONEUSNICKNAME(irc::Server *srv, irc::User usr) {return (":Erroneus nickname"); (void)srv; (void)usr;};
std::string ERR_NICKNAMEINUSE(irc::Server *srv, irc::User usr) {return (":Nickname is already in use"); (void)srv; (void)usr;};

#endif