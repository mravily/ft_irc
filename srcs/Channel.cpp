/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravily <mravily@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 15:42:04 by mravily           #+#    #+#             */
/*   Updated: 2022/07/22 16:15:22 by mravily          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

bool irc::Channel::isOperator(irc::User *usr)
{
	for (std::vector<irc::User*>::iterator it = _operator.begin(); it != _operator.end(); it++)
		if ((*it) == usr)
			return (true);
	return (false);
}

bool irc::Channel::findMode(std::string modes)
{
	if (!this->_mode.size())
		return (false);
	for (std::string::iterator it = modes.begin(); it != modes.end(); it++)
	{
		if (_mode.size())
			if (this->_mode.find(*it) == std::string::npos)
				return (false);
	}
	return (true);
}

std::vector<irc::User *> irc::Channel::getUsers()
{
	std::vector<irc::User *> Users(this->getOperator());
	Users.insert(Users.end(), _users.begin(), _users.end());
	return (Users);
}

std::string irc::Channel::getCurrentDate()
{
	time_t now = time(NULL);
	gmtime(&now);
	std::stringstream tt;
	tt << now;
	return (tt.str());
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

void irc::Channel::addUser(irc::User *usr) {_users.push_back(usr);};

/*
** @brief Chercher un user dans le list donner et le retire
** @param list liste d'user dans la quelle chercher
** @param toFind User à trouver
** @return Renvoi true si l'user a été trouver
*/
bool findEraseUser(std::vector<irc::User *> &list, irc::User *toFind, irc::Channel *chan, std::string message)
{
	std::vector<irc::User *>::iterator itOpe(list.begin());
	for (; itOpe != list.end(); itOpe++)
	{
		if ((*itOpe) == toFind)
		{
			toFind->broadcast(chan, message, 0);
			list.erase(itOpe);
			return (true);
			if (!list.size())
				break ;
		}
	}
	return (false);
}

void irc::Channel::eraseUser(std::vector<irc::User *>& list, std::string toFind)
{
	std::vector<irc::User *>::iterator it(list.begin());
	for (; it != list.end(); it++)
	{
		if (!toFind.compare((*it)->getNickname()))
		{
			list.erase(it);
			break ;
		}
	}
}

void printStrVector(std::vector<std::string> list)
{
	std::vector<std::string>::iterator it(list.begin());
	for(; it != list.end(); it++)
		std::cout << "list: " << (*it) << std::endl;
}

void irc::Channel::addMode(irc::User* usr, std::string modestring, std::vector<std::string> arg)
{

	bool change = false;
	printStrVector(arg);
	std::vector<std::string>::iterator ita(arg.begin());
	std::string::iterator it(modestring.begin());
	std::string::iterator ite(modestring.end());
	for (; it != ite; it++)
	{
		if ((*it) == 'o' && !arg.size())
		{
			usr->reply(461);
			modestring.erase(modestring.find('o'));
			return ;
		}
		else if ((*it) == 'o' && isOperator(usr) == false)
		{
			usr->reply(481);
			modestring.erase(modestring.find('o'));
		}
		else if ((*it) == 'o' && isOperator(usr) == true)
		{
			irc::User* toModif = findUserChan(getUser(), (*ita));
			if (!toModif && !knowOper(findUserChan(getOperator(), (*ita))))
			{
				usr->reply(401);   		// ERR_NOSUCHNICK
				ita++;
				return ;
			}
			else if (toModif && usr != toModif)
			{
				change = true;
				toModif->setMode((*it));
				_operator.push_back(toModif);
				eraseUser(_users, toModif->getNickname());
				usr->addWaitingSend(":" + usr->getClient() + " MODE " + getName() + " +o :" + toModif->getNickname() + CRLF);
				toModif->addWaitingSend(":" + usr->getClient() + " MODE " + getName() + " +o :" + toModif->getNickname() + CRLF);
				ita++;
			}
			modestring.erase(modestring.find('o'));
		}
		if (getModes().find(*it) != std::string::npos)
			modestring.erase(modestring.find((*it)));
	}
	if (modestring.size() && isOperator(usr))
		setModes(usr, modestring);
	else if (!isOperator(usr) && change == false)
		usr->reply(482, this);
}

void irc::Channel::setModes(irc::User* usr, std::string modestring)
{
	_mode += modestring;
	usr->broadcast(this, " MODE " + getName() + " +" + modestring + " :" + usr->getNickname(), 0);
}

void irc::Channel::rmModes(irc::User* usr, std::string modestring)
{
	bool change = false;
	std::string::iterator it(modestring.begin());
	for (; it != modestring.end(); it++)
		if (getModes().size() && _mode.find((*it)) != std::string::npos)
		{
			_mode.erase(_mode.find((*it)));
			change = true;
		}
	if (change == true && modestring.size())
		usr->broadcast(this, " MODE " + getName() + " -" + modestring + " :" + usr->getNickname(), 0);
}

void irc::Channel::removeMode(irc::User* usr, std::string modestring, std::vector<std::string> arg)
{

	bool change = false;
	std::string::iterator it(modestring.begin());
	std::string::iterator ite(modestring.end());

	std::vector<std::string>::iterator itt(arg.begin());
	for (; it != ite; it++)
	{
		if ((*it) == 'o' && !arg.size())
		{
			usr->reply(461);
			modestring.erase(modestring.find('o'));
			return ;
		}
		else if ((*it) == 'o' && isOperator(usr) == false)
		{
			change = true;
			usr->reply(481); 
			modestring.erase(modestring.find('o'));
		}
		else if ((*it) == 'o' && isOperator(usr) == true)
		{
			irc::User* toModif = findUserChan(getOperator(), (*itt++));
			if (!toModif)
			{
				usr->reply(401);   		// ERR_NOSUCHNICK
				return ;
			}
			else if (usr == toModif)
			{
				change = true;
				_users.push_back(usr);
				eraseUser(_operator, usr->getNickname());
				usr->addWaitingSend(":" + usr->getClient() + " MODE " + getName() + " -o :" + usr->getNickname() + CRLF);
				modestring.erase(modestring.find((*it)));
			}
			else if (usr != toModif)
			{
				change = true;
				_users.push_back(toModif);
				eraseUser(_operator, toModif->getNickname());
				usr->addWaitingSend(":" + usr->getClient() + " MODE " + getName() + " -o :" + toModif->getNickname() + CRLF);
				toModif->addWaitingSend(":" + usr->getClient() + " MODE " + getName() + " -o :" + toModif->getNickname() + CRLF);
				modestring.erase(modestring.find((*it)));
			}
		}
	}
	if (modestring.size() && isOperator(usr))
		rmModes(usr, modestring);
	else if (change == false)
		usr->reply(482, this);
}

void irc::Channel::removeUser(irc::User *usr, std::string message)
{
	bool find = false;
	if (!(find = findEraseUser(_operator, usr, this, message)))
		find = findEraseUser(_users, usr, this, message);
	if (find == false)
		usr->reply(442, this);
}

void irc::Channel::deleteUser(irc::User *target)
{
	std::vector<User *>::iterator it = this->_operator.begin();
	while (it != this->_operator.end())
	{
		if (*it == target)
		{
			this->_operator.erase(it++);
			return;
		}
		else
			++it;
	}
	for (std::vector<User *>::iterator it = this->_users.begin(); it != this->_users.end(); it++)
	{
		if (*it == target)
		{
			this->_users.erase(it);
			return;
		}
	}
}

void irc::Channel::kickUser(irc::User *usr, irc::User *target, std::string reason)
{
	usr->broadcast(this, " KICK " + this->_name + " " + target->getNickname() + " " + reason, 0);
	deleteUser(target);
}

bool irc::Channel::knowUser(irc::User* usr)
{
	std::vector<User *> users = getUsers();
	for (std::vector<User *>::iterator it = users.begin(); it != users.end(); it++)
		if ((*it) == usr)
			return (true);
	return (false);
}

bool irc::Channel::knowOper(irc::User* usr)
{
	std::vector<User *> users = getOperator();
	for (std::vector<User *>::iterator it = users.begin(); it != users.end(); it++)
		if ((*it) == usr)
			return (true);
	return (false);	
}

irc::Channel::Channel(bool type, std::string name, irc::User* ope) : _private(type), _name(name), _mode("nt"), _datatime(getCurrentDate())
{
	this->_operator.push_back(ope);
}

irc::Channel::~Channel() {};
