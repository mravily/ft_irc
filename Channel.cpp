/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravily <mravily@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 15:42:04 by mravily           #+#    #+#             */
/*   Updated: 2022/07/10 15:44:22 by mravily          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include <sstream>

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

	for (std::vector<User*>::iterator it = _operator.begin(); it != _operator.end(); it++)
		responseList += "@" + (*it)->getNickname() + " ";
	for (std::vector<User*>::iterator it = _users.begin(); it != _users.end(); it++)
		responseList += (*it)->getNickname() + " ";

	return (responseList);
}
void irc::Channel::addUser(irc::User *usr) {_users.push_back(usr); _capacity++;};

irc::Channel::Channel(bool type, std::string name, irc::User* ope, std::string pass) : _private(type), _name(name), _mode("nt"), _password(pass), _capacity(1)
{
	this->_operator.push_back(ope);
}

irc::Channel::~Channel() {};
