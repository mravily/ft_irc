/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Replies.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravily <mravily@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 21:25:38 by mravily           #+#    #+#             */
/*   Updated: 2022/07/22 17:33:31 by nayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLIES_HPP
#define REPLIES_HPP

#include "Server.hpp"
#include "User.hpp"


/*
** Réponses minimum à renvoyer lors d'une connexion au server
*/
std::string RPL_WELCOME(irc::Server *srv, irc::User usr, irc::Channel *chan) {return (WELCOMEART + usr.getNickname() + "!" + usr.getUsername() + "@" + LYELLOW + usr.getHostname() + STOP); (void)srv; (void)chan;}
std::string RPL_YOURHOST(irc::Server *srv, irc::User usr, irc::Channel *chan) {return (":Your Host is \e[93m" + usr.getHostname() + STOP + ", running version " + srv->getVersion()); (void)chan;}
std::string RPL_CREATED(irc::Server *srv, irc::User usr, irc::Channel *chan) {return (":This server was created \e[1;94m" + srv->getDatatime() + "\e[0m"); (void)usr; (void)chan;}
std::string RPL_MYINFO(irc::Server *srv, irc::User usr, irc::Channel *chan) {return (usr.getHostname() + " IRCHobbs-" + srv->getVersion() + " " + srv->getUsrMode() + " " + srv->getChanMode()); (void)chan;};
std::string RPL_UMODEIS(irc::Server *srv, irc::User usr, irc::Channel *chan) {return (CYAN + usr.getMode() + STOP); (void)srv; (void)chan;};

/* MODE Replies 401 502 501*/
std::string ERR_NOSUCHNICK(irc::Server *srv, irc::User usr, irc::Channel *chan) {return (":No such nick/channel"); (void)srv; (void)usr; (void)chan;};
std::string ERR_USERSDONTMATCH(irc::Server *srv, irc::User usr, irc::Channel *chan) {return (":Can't view modes for other users"); (void)srv; (void)usr; (void)chan;};
std::string ERR_UMODEUNKNOWNFLAG(irc::Server *srv, irc::User usr, irc::Channel *chan) {return (":Unknown MODE flag"); (void)srv; (void)usr; (void)chan;};

/* PASS Replies 461 462 464 */
std::string ERR_NEEDMOREPARAMS(irc::Server *srv, irc::User usr, irc::Channel *chan) {return (":Not enough parameters"); (void)srv; (void)usr; (void)chan;};
std::string ERR_ALREADYREGISTERED(irc::Server *srv, irc::User usr, irc::Channel *chan) {return (":You may not reregister"); (void)srv; (void)usr; (void)chan;};
std::string ERR_PASSWDMISMATCH(irc::Server *srv, irc::User usr, irc::Channel *chan) {return (":Password incorrect"); (void)srv; (void)usr; (void)chan;};

/* NICK Replies 431 432 433 */
std::string ERR_NONICKNAMEGIVEN(irc::Server *srv, irc::User usr, irc::Channel *chan) {return (":No nickname given"); (void)srv; (void)usr; (void)chan;};
std::string ERR_ERRONEUSNICKNAME(irc::Server *srv, irc::User usr, irc::Channel *chan) {return (":Erroneus nickname"); (void)srv; (void)usr; (void)chan;};
std::string ERR_NICKNAMEINUSE(irc::Server *srv, irc::User usr, irc::Channel *chan) {return (usr.getNickname() + " Nickname is already in use :" + usr.getNickname()); (void)srv; (void)usr; (void)chan;};

// (JOIN) 331 - 353 - 366 - 324 - 403
std::string RPL_NOTOPIC(irc::Server *srv, irc::User usr, irc::Channel *chan) {return (chan->getName() + " :No topic is set"); (void)srv; (void)usr;}
std::string RPL_TOPIC(irc::Server *srv, irc::User usr, irc::Channel *chan) {return (chan->getName() + " :" + chan->getTopic()); (void)srv; (void)usr;}
std::string RPL_TOPICWHOTIME(irc::Server *srv, irc::User usr, irc::Channel *chan) {return (chan->getName() + " " + chan->getCreator() + " " + chan->getDate()); (void)srv; (void)usr;}
std::string RPL_NAMEREPLY(irc::Server *srv, irc::User usr, irc::Channel *chan) { return ("= " + chan->getName() + " :" + chan->getListUsers()); (void)srv; (void)usr;}
std::string RPL_ENDNAMES(irc::Server *srv, irc::User usr, irc::Channel *chan) {return (chan->getName() + " :END on /NAMES list."); (void)srv; (void)usr;}
std::string ERR_NOSUCHCHANNEL(irc::Server *srv, irc::User usr, irc::Channel *chan) {return (chan->getName() + " :No such channel"); (void)srv; (void)usr;}
std::string RPL_CHANNELMODEIS(irc::Server *srv, irc::User usr, irc::Channel *chan) {return (chan->getName()  + " +" + chan->getModes()); (void)srv; (void)usr;}
std::string RPL_CREATIONTIME(irc::Server *srv, irc::User usr, irc::Channel *chan) {return (chan->getName()  + " :" + chan->getDatatime()); (void)srv; (void)usr;}

std::string ERR_BADCHANNELKEY(irc::Server *srv, irc::User usr, irc::Channel *chan) {return (chan->getName()) + " :Cannot join channel (incorrect channel key)"; (void)usr; (void)srv;};
std::string ERR_CHANNELISFULL(irc::Server *srv, irc::User usr, irc::Channel *chan) {return (chan->getName()) + " :Cannot join channel (channel is full)"; (void)usr; (void)srv;};

// 441 - 442 - 443
std::string ERR_USERNOTINCHANNEL(irc::Server *srv, irc::User usr, irc::Channel *chan) {return ("target " + chan->getName()) + " :They are not on that channel"; (void)usr; (void)srv;};
std::string ERR_NOTONCHANNEL(irc::Server *srv, irc::User usr, irc::Channel *chan) {return (chan->getName()) + " :You're not on that channel"; (void)usr; (void)srv;};
std::string ERR_USERONCHANNEL(irc::Server *srv, irc::User usr, irc::Channel *chan) {return ("user " + chan->getName()) + " :is already on channel"; (void)srv; (void)usr;};

// (LIST) 321 - 322 - 323
std::string RPL_LISTSTART(irc::Server *srv, irc::User usr, irc::Channel *chan) {return ("\e[1;40mChannels List:\e[0m"); (void)srv; (void)usr; (void)chan;}
std::string RPL_LIST(irc::Server *srv, irc::User usr, irc::Channel *chan) {return (BOLD + chan->getName() + STOP + " " + chan->getUserSize() + " :[+" + CYAN + chan->getModes() + STOP + "] " + ITALIC + YELLOW + chan->getTopic() + STOP); (void)srv; (void)usr;}
std::string RPL_LISTEND(irc::Server *srv, irc::User usr, irc::Channel *chan) {return ("\e[1;40mEnd of List\e[0m"); (void)srv; (void)usr; (void)chan;}

// 402 - 482
//std::string ERR_NOSUCHSERVER(irc::Server *srv, irc::User usr, irc::Channel *chan) {return (" :Cannot find"); (void)usr; (void)srv; (void)chan;}
std::string ERR_CHANOPRIVSNEEDED(irc::Server *srv, irc::User usr, irc::Channel *chan) {return (chan->getName() + " :You're not channel operator"); (void)usr; (void)srv;}

// 381

std::string RPL_YOUREOPER(irc::Server *srv, irc::User usr, irc::Channel *chan) { return ("You are now an IRC operator"); (void)usr; (void)srv; (void)chan; }

std::string ERR_NOPRIVILEGES(irc::Server *srv, irc::User usr, irc::Channel *chan) {return (":Permission Denied- You're not an IRC operator"); (void)usr; (void)srv; (void)chan;};

//473
std::string ERR_INVITEONLYCHAN(irc::Server *srv, irc::User usr, irc::Channel *chan) { return (chan->getName() + " :Cannot join channel (+i) invitation only."); (void)usr; (void)srv;}

// (PRIVMSG/NOTICE)  412 - 404
std::string ERR_NOTEXTTOSEND(irc::Server *srv, irc::User usr, irc::Channel *chan) {return (" :Not enough parameters given"); (void)usr; (void)srv; (void)chan;}
std::string ERR_CANNOTSENDTOCHAN(irc::Server *srv, irc::User usr, irc::Channel *chan) {return (chan->getName() + " :You cannot send external messages to this channel whilst the +n (noextmsg) mode is set."); (void)usr; (void)srv;}

//402 && 723
std::string ERR_NOSUCHSERVER(irc::Server *srv, irc::User usr, irc::Channel *chan) {return (/*server name +*/" :No such server"); (void)usr; (void)srv; (void)chan;}
std::string ERR_NOPRIVS(irc::Server *srv, irc::User usr, irc::Channel *chan) {return (/*priv + */" :Insufficient oper privileges."); (void)usr; (void)srv; (void)chan;}
#endif
