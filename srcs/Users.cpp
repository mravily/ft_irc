/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Users.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravily <mravily@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 18:08:56 by mravily           #+#    #+#             */
/*   Updated: 2022/07/14 19:52:12 by mravily          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Replies.hpp"

std::string irc::User::printStatus()
{
	if (_status == 0)
		return ("CONNECTED");
	else if (_status == 1)
		return ("AUTHENFICATED");
	else if (_status == 2)
		return ("REGISTERED");
	else if (_status == 3)
		return ("ONLINE");
	else if (_status == 4)
		return ("LEAVE");
	else if (_status == 5)
		return ("ERROR");
	else
		return ("NONE");
};

int irc::User::getFd() {return (_fd);};
std::string irc::User::getMode() {return (_mode);};
std::string irc::User::getNickname() {return (_nickname);};
std::string irc::User::getRealname() {return (_realname);};
std::string irc::User::getUsername() {return (_username);};
std::string irc::User::getHostname() {return (_hostname);};
std::string irc::User::getHostaddr() {return (_hostaddr);};
std::string irc::User::getClient() {return (getNickname() + "!" + getUsername() + "@" + getHostname());};
irc::stats irc::User::getStatus() {return (_status);};
irc::Server* irc::User::getServer() {return (_server);};

void irc::User::setStatus(irc::stats newStatus) {this->_status = newStatus;};
void irc::User::setNickname(std::string nick) {this->_nickname = nick;};
void irc::User::setUsername(std::string usrname) {this->_username = usrname;};
void irc::User::setRealname(std::string realname) {this->_realname = realname;};
void irc::User::setHostname(std::string hostname) {this->_hostname = hostname;};
void irc::User::setMode(std::string modestring)
{
	bool minus = false;
	std::string::iterator it(modestring.begin());
	for (; it != modestring.end(); it++)
	{
		if ((*it) == '-')
			minus = true;
		else if ((*it) == '+')
			minus = false;
		else if (minus == false)
			_mode += (*it);
		else
			_mode.erase(_mode.find((*it)));
	}
}


void irc::User::addWaitingSend(std::string newReply)
{
	_waitingSend.push_back(newReply);
}

std::string irc::User::getReplies(int code, irc::Channel *chan)
{
	std::string scode = std::to_string(code);
	while (scode.length() < 3)
		scode = "0" + scode;
	std::string toSent(":" + getClient() + " " + scode + " " + getNickname() + " " + _rpl.find(code)->second(getServer(), *this, chan));
	// std::cout << toSent << std::endl;
	return(toSent);
}

void irc::User::reply(int code, irc::Channel *chan)
{
	std::string answer(getReplies(code, chan));
	_waitingSend.push_back(answer + CRLF);
}

void irc::User::registration()
{
	reply(001);
	reply(002);
	reply(003);
	reply(004);
	reply(221);
	setStatus(irc::REGISTERED);
}

void irc::User::processReply()
{
	std::cout << printStatus() << std::endl;
	
	if (checkBit(0))
		std::cout << (_mandatory & (1 << 0)) << std::endl;
	if (!checkBit(0) && getStatus() == irc::CONNECTED && _cmds.size())
	{
		puts("IN");
		this->setStatus(irc::LEAVE);
		this->addWaitingSend((std::string)"ERROR :Need password" + CRLF);
	}
	else if (_mandatory == 7 && getStatus() != REGISTERED && getStatus() != ONLINE && getStatus() != LEAVE && getStatus() != ERROR)
		registration();

	// Bufferize toutes les réponses pour les envoyer avec send()
	// std::cout << "[SERVER] Réponse du server" << std::endl;
	std::string buffer;
	std::vector<std::string>::iterator it(_waitingSend.begin());
	for (; it != _waitingSend.end(); it++)
	{
		std::cout << (*it) << std::endl;
		buffer += (*it);
	}
	if (buffer.length())
		send(getFd(), buffer.c_str(), buffer.length(), 0);

	_cmds.erase(_cmds.begin(), _cmds.end());
	_waitingSend.erase(_waitingSend.begin(), _waitingSend.end());
	buffer.clear();
	puts("OUT PROCESS");
}


/*
** @brief Récupère les messages de l'utilisateur envoyer sur le socket
** et les splits à chaque CRLF
*/
void irc::User::getMessages()
{
	puts("IN MESSAGE");
	size_t size;
	char buffer[BUFFER_SIZE + 1];
	size = recv(this->_fd, &buffer, BUFFER_SIZE, 0);
	buffer[size] = '\0';

	std::cout << "Buffer: " << buffer << std::endl;
	std::string buf(buffer);
	std::vector<std::string> messages(split(buf, CRLF));
	std::vector<std::string>::iterator it(messages.begin());
	for (; it != messages.end(); it++)
	{
		if (!(*it).length())
			continue ;
		_cmds.push_back(new irc::Command((*it)));
	}

	// Compare les prefix des commandes reçu avec les commandes users disponible
	std::vector<Command *>::iterator its(_cmds.begin());
	for (; its != _cmds.end(); its++)
	{
		std::map<std::string, cmd_funct>::iterator itm(_funct.begin());
		// std::cout << "Get Message->prefix: " << (*its)->getPrefix() << std::endl;
		for(; itm != _funct.end(); itm++)
		{
			// std::cout << "(*itm).first: " << (*itm).first << std::endl;
			// std::cout << "(*its)->getPrefix(): " << (*its)->getPrefix() << std::endl;
			// std::cout << (*itm).first <<  " " << (*itm).second << " ;) " << std::endl;
			if ((*itm).first.compare((*its)->getPrefix()) == 0)
			{
				(*itm).second(getServer(), this, (*its));
			}
		}
	}
	puts("OUT MESSAGE");
}

void irc::User::setBits(int index){_mandatory = _mandatory | (1 << index);}

irc::User::User(irc::Server *srv,int socket, sockaddr_in address) : _server(srv), _fd(socket), _address(address), _status(CONNECTED), _mode("w"), _nickname("*"), _reason("leaving")
{
	_mandatory = 0;
	fcntl(this->_fd, F_SETFL, O_NONBLOCK);

	_hostaddr = inet_ntoa(address.sin_addr);
	char hostname[NI_MAXHOST];
	if (getnameinfo((struct sockaddr *)&_address, sizeof(_address), hostname, NI_MAXHOST, NULL, 0, NI_NUMERICSERV) != 0)
		DisplayError("Getnameinfo: ");
	setHostname(hostname);
	setCmd();
	setReplies();

	// printf("hostname: %s\n", hostname);
	// printf("hostaddr: %s\n", _hostaddr.c_str());
};

void irc::User::broadcast(irc::Channel *chan, std::string message, irc::User *without)
{
	std::vector<User *> users(chan->getUsers());
	std::vector<User *>::iterator itUsers(users.begin());
	for (; itUsers != users.end(); itUsers++)
	{
		if ((*itUsers) != without)
			(*itUsers)->addWaitingSend(":" + this->getClient() + message + CRLF);
		if ((*itUsers) != this)
			(*itUsers)->processReply();
	}
}

irc::User::~User()
{
	// std::vector<Command *>::iterator it(_cmds.begin());
	// for (; it != _cmds.end(); it++)
	// 	delete (*it);
};

void irc::User::setCmd()
{
	// Set les functions de l'utilisateur
	_funct.insert(std::make_pair<std::string, cmd_funct>("PASS", PASS));
	_funct.insert(std::make_pair<std::string, cmd_funct>("NICK", NICK));
	_funct.insert(std::make_pair<std::string, cmd_funct>("USER", USER));
	_funct.insert(std::make_pair<std::string, cmd_funct>("MODE", MODE));
	_funct.insert(std::make_pair<std::string, cmd_funct>("PING", PING));
	_funct.insert(std::make_pair<std::string, cmd_funct>("JOIN", JOIN));
	_funct.insert(std::make_pair<std::string, cmd_funct>("QUIT", QUIT));
	_funct.insert(std::make_pair<std::string, cmd_funct>("PART", PART));
	_funct.insert(std::make_pair<std::string, cmd_funct>("PRIVMSG", PRIVMSG));
	_funct.insert(std::make_pair<std::string, cmd_funct>("LIST", LIST));
	_funct.insert(std::make_pair<std::string, cmd_funct>("TOPIC", TOPIC));
}

void irc::User::setReplies()
{
	_rpl.insert(std::make_pair<int, rpl_funct>(001, RPL_WELCOME));
	_rpl.insert(std::make_pair<int, rpl_funct>(002, RPL_YOURHOST));
	_rpl.insert(std::make_pair<int, rpl_funct>(003, RPL_CREATED));
	_rpl.insert(std::make_pair<int, rpl_funct>(004, RPL_MYINFO));
	_rpl.insert(std::make_pair<int, rpl_funct>(221, RPL_UMODEIS));
	_rpl.insert(std::make_pair<int, rpl_funct>(321, RPL_LISTSTART));
	_rpl.insert(std::make_pair<int, rpl_funct>(322, RPL_LIST));
	_rpl.insert(std::make_pair<int, rpl_funct>(323, RPL_LISTEND));
	_rpl.insert(std::make_pair<int, rpl_funct>(324, RPL_CHANNELMODEIS));
	_rpl.insert(std::make_pair<int, rpl_funct>(329, RPL_CREATIONTIME));
	_rpl.insert(std::make_pair<int, rpl_funct>(331, RPL_NOTOPIC));
	_rpl.insert(std::make_pair<int, rpl_funct>(332, RPL_TOPIC));
	_rpl.insert(std::make_pair<int, rpl_funct>(353, RPL_NAMEREPLY));
	_rpl.insert(std::make_pair<int, rpl_funct>(366, RPL_ENDNAMES));
	_rpl.insert(std::make_pair<int, rpl_funct>(401, ERR_NOSUCHNICK));
	_rpl.insert(std::make_pair<int, rpl_funct>(403, ERR_NOSUCHCHANNEL));
	_rpl.insert(std::make_pair<int, rpl_funct>(431, ERR_NONICKNAMEGIVEN));
	_rpl.insert(std::make_pair<int, rpl_funct>(432, ERR_ERRONEUSNICKNAME));
	_rpl.insert(std::make_pair<int, rpl_funct>(433, ERR_NICKNAMEINUSE));
	_rpl.insert(std::make_pair<int, rpl_funct>(442, ERR_NOTONCHANNEL));
	_rpl.insert(std::make_pair<int, rpl_funct>(461, ERR_NEEDMOREPARAMS));
	_rpl.insert(std::make_pair<int, rpl_funct>(462, ERR_ALREADYREGISTERED));
	_rpl.insert(std::make_pair<int, rpl_funct>(464, ERR_PASSWDMISMATCH));
	_rpl.insert(std::make_pair<int, rpl_funct>(471, ERR_CHANNELISFULL));
	_rpl.insert(std::make_pair<int, rpl_funct>(475, ERR_BADCHANNELKEY));
	_rpl.insert(std::make_pair<int, rpl_funct>(482, ERR_CHANOPRIVSNEEDED));
	_rpl.insert(std::make_pair<int, rpl_funct>(501, ERR_UMODEUNKNOWNFLAG));
	_rpl.insert(std::make_pair<int, rpl_funct>(502, ERR_USERSDONTMATCH));
}

void irc::User::printUser()
{
	std::cout << "FD: " << getFd() << "\n"
	<< "Status: " << printStatus() << "\n"
	<< "Mode: " << getMode() << "\n"
	<< "Nickname: " << getNickname() << "\n"
	<< "Username: " << getUsername() << "\n"
	<< "Realname: " << getRealname() << "\n"
	<< "Hostaddr: " << getHostaddr() << "\n"
	<< "Hostname: " << getHostname() << std::endl;
}

void irc::User::setReason(std::string trailer) { this->_reason = trailer; }

std::string irc::User::getReason() { return _reason; }
