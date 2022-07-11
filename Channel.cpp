/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravily <mravily@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 15:42:04 by mravily           #+#    #+#             */
/*   Updated: 2022/07/11 16:12:33 by nayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

std::vector<irc::User *> irc::Channel::getUsers()
{
	std::vector<irc::User *> Users(this->getOperator());
	Users.insert(Users.end(), _users.begin(), _users.end());
	
	std::vector<User *>::iterator it(Users.begin());
	for (; it != Users.end(); it++)
		std::cout << "User: " << (*it)->getNickname() << std::endl;
	return (Users);
}

void irc::Channel::setDatatime()
{
		time_t now = time(NULL);
		gmtime(&now);
		std::stringstream tt;
		tt << now;
		this->_datatime = tt.str();
}

std::string irc::Channel::getListUsers()
{
	std::string responseList;

	for (std::vector<irc::User*>::iterator it = _operator.begin(); it != _operator.end(); it++)
		responseList += "@" + (*it)->getNickname() + " ";
	for (std::vector<irc::User*>::iterator it = _users.begin(); it != _users.end(); it++)
		responseList += (*it)->getNickname() + " ";

	return (responseList);
}

std::string irc::Channel::getUserSize()
{
	std::stringstream ss;
	ss << this->_users.size() + this->_operator.size();
	return (ss.str());
}

void irc::Channel::addUser(irc::User *usr) {_users.push_back(usr); _capacity++;};

/*
** @brief Chercher un user dans le list donner et le retire
** @param list liste d'user dans la quelle chercher
** @param toFind User à trouver
** @return Renvoi true si l'user a été trouver
*/
bool findUser(std::vector<irc::User *> &list, irc::User *toFind, irc::Channel *chan)
{
	std::vector<irc::User *>::iterator itOpe(list.begin());
	for (; itOpe != list.end(); itOpe++)
	{
		if ((*itOpe) == toFind)
		{
			toFind->broadcast(chan, (" PART :" + chan->getName()), 0);
			list.erase(itOpe);
			return (true);
			if (!list.size())
				break ;
		}
	}
	return (false);
}

void irc::Channel::removeUser(irc::User *usr)
{
	bool find = false;
	if (!(find = findUser(_operator, usr, this)))
		find = findUser(_users, usr, this);
	// Si le dernier OPE quitte le server, les droits OPE sont attribuer a un autre USER
	std::cout << "Ope.size: " << _operator.size() << std::endl;
	std::cout << "Usr.size: " << _users.size() << std::endl;
	if (!_operator.size() && _users.size())
		puts("NO MORE OPE BUT LEFT USER, DO SOMETHING");
	if (find == false)
		usr->reply(442, this);
}

irc::Channel::Channel(bool type, std::string name, irc::User* ope, std::string pass) : _private(type), _name(name), _mode("nt"), _password(pass), _capacity(1)
{
	this->_operator.push_back(ope);
}

irc::Channel::~Channel() {};
