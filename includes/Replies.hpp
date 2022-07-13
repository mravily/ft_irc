/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Replies.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravily <mravily@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 21:25:38 by mravily           #+#    #+#             */
/*   Updated: 2022/07/13 16:17:03 by nayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLIES_HPP
#define REPLIES_HPP

#include "Server.hpp"
#include "User.hpp"


/*
** Réponses minimum à renvoyer lors d'une connexion au server
*/
std::string RPL_WELCOME(irc::Server *srv, irc::User usr, irc::Channel *chan) {return (":Welcome to the IRC Hobbs Network, " + usr.getNickname() + "!" + usr.getUsername() + "@" + usr.getHostname()); (void)srv; (void)chan;}
std::string RPL_YOURHOST(irc::Server *srv, irc::User usr, irc::Channel *chan) {return (":Your Host is " + usr.getHostname() + ", running version " + srv->getVersion()); (void)chan;}
std::string RPL_CREATED(irc::Server *srv, irc::User usr, irc::Channel *chan) {return (":This server was created " + srv->getDatatime() + ""); (void)usr; (void)chan;}
std::string RPL_MYINFO(irc::Server *srv, irc::User usr, irc::Channel *chan) {return (usr.getHostname() + " IRCHobbs-" + srv->getVersion() + " " + srv->getUsrMode() + " " + srv->getChanMode() + " :FIJLXabefghjkloqv"); (void)chan;};
std::string RPL_UMODEIS(irc::Server *srv, irc::User usr, irc::Channel *chan) {return (usr.getMode()); (void)srv; (void)chan;};

/* MODE Replies 401 502 501*/
std::string ERR_NOSUCHNICK(irc::Server *srv, irc::User usr, irc::Channel *chan) {return (":No such nick/channel"); (void)srv; (void)usr; (void)chan;};
std::string ERR_USERSDONTMATCH(irc::Server *srv, irc::User usr, irc::Channel *chan) {return (":Cant change mode for other users"); (void)srv; (void)usr; (void)chan;};
std::string ERR_UMODEUNKNOWNFLAG(irc::Server *srv, irc::User usr, irc::Channel *chan) {return (":Unknown MODE flag"); (void)srv; (void)usr; (void)chan;};

/* PASS Replies 461 462 464 */
std::string ERR_NEEDMOREPARAMS(irc::Server *srv, irc::User usr, irc::Channel *chan) {return (":Not enough parameters"); (void)srv; (void)usr; (void)chan;};
std::string ERR_ALREADYREGISTERED(irc::Server *srv, irc::User usr, irc::Channel *chan) {return (":You may not reregister"); (void)srv; (void)usr; (void)chan;};
std::string ERR_PASSWDMISMATCH(irc::Server *srv, irc::User usr, irc::Channel *chan) {return (":Password incorrect"); (void)srv; (void)usr; (void)chan;};

/* NICK Replies 431 432 433 */
std::string ERR_NONICKNAMEGIVEN(irc::Server *srv, irc::User usr, irc::Channel *chan) {return (":No nickname given"); (void)srv; (void)usr; (void)chan;};
std::string ERR_ERRONEUSNICKNAME(irc::Server *srv, irc::User usr, irc::Channel *chan) {return (":Erroneus nickname"); (void)srv; (void)usr; (void)chan;};
std::string ERR_NICKNAMEINUSE(irc::Server *srv, irc::User usr, irc::Channel *chan) {return (":" + usr.getNickname()); (void)srv; (void)usr; (void)chan;};

// (JOIN) 331 - 353 - 366 - 324 - 403
std::string RPL_NOTOPIC(irc::Server *srv, irc::User usr, irc::Channel *chan) {return (chan->getName() + " :No topic is set"); (void)srv; (void)usr;}
std::string RPL_TOPIC(irc::Server *srv, irc::User usr, irc::Channel *chan) {return (chan->getName() + " :" + chan->getTopic()); (void)srv; (void)usr;}
std::string RPL_NAMEREPLY(irc::Server *srv, irc::User usr, irc::Channel *chan) { return ("= " + chan->getName() + " :" + chan->getListUsers()); (void)srv; (void)usr;}
std::string RPL_ENDNAMES(irc::Server *srv, irc::User usr, irc::Channel *chan) {return (chan->getName() + " :END on /NAMES list."); (void)srv; (void)usr;}
std::string ERR_NOSUCHCHANNEL(irc::Server *srv, irc::User usr, irc::Channel *chan) {return (chan->getName() + " :No such channel"); (void)srv; (void)usr;}
std::string RPL_CHANNELMODEIS(irc::Server *srv, irc::User usr, irc::Channel *chan) {return (chan->getName()  + " +" + chan->getModes()); (void)srv; (void)usr;}
std::string RPL_CREATIONTIME(irc::Server *srv, irc::User usr, irc::Channel *chan) {return (chan->getName()  + " :" + chan->getDatatime()); (void)srv; (void)usr;}

std::string ERR_BADCHANNELKEY(irc::Server *srv, irc::User usr, irc::Channel *chan) {return (chan->getName()) + " :Cannot join channel (incorrect channel key)"; (void)usr; (void)srv;};
std::string ERR_CHANNELISFULL(irc::Server *srv, irc::User usr, irc::Channel *chan) {return (chan->getName()) + " :Cannot join channel (channel is full)"; (void)usr; (void)srv;};
std::string ERR_NOTONCHANNEL(irc::Server *srv, irc::User usr, irc::Channel *chan) {return (chan->getName()) + " :You're not on that channel"; (void)usr; (void)srv;};

// (LIST) 321 - 322 - 323
std::string RPL_LISTSTART(irc::Server *srv, irc::User usr, irc::Channel *chan) {return ("\002Channels List: "); (void)srv; (void)usr; (void)chan;}
std::string RPL_LIST(irc::Server *srv, irc::User usr, irc::Channel *chan) {return (chan->getName() + " " + chan->getUserSize() + " :[+" + chan->getModes() + "] " + chan->getTopic()); (void)srv; (void)usr;}
std::string RPL_LISTEND(irc::Server *srv, irc::User usr, irc::Channel *chan) {return (":\002End of List"); (void)srv; (void)usr; (void)chan;}

// 402
std::string ERR_NOSUCHSERVER(irc::Server *srv, irc::User usr, irc::Channel *chan) {return (" :Cannot find"); (void)usr; (void)srv; (void)chan;}

#endif