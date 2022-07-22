/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravily <mravily@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 15:19:17 by mravily           #+#    #+#             */
/*   Updated: 2022/07/20 23:10:23 by mravily          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include <map>
#include <vector>
#include <poll.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <ctime>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <cctype>
#include <signal.h>

#include "Channel.hpp"
#include "User.hpp"
#include "color.hpp"

#define RPL_JOIN_ 011
#define RPL_MODE_ 012

irc::User* findUserSrv(irc::Server *srv, std::string toFind);
irc::User* findUserChan(std::vector<irc::User *> list, std::string toFind);
irc::Channel* findChan(irc::Server *srv, std::string toFind);
bool checkAllowMode(std::string allowMode, std::string toCheck);
void chanMode(irc::Server *srv, irc::User *usr, irc::Command *cmd);
void userMode(irc::Server *srv, irc::User *usr, irc::Command *cmd);
bool isDigits(const std::string &str);

namespace irc
{
	class User;
	class Channel;

	class Server
	{
		friend class User;
		friend class Channel;

	private:
		std::string _version;
		int _socketServer;
		struct sockaddr_in _addrServer;
		std::vector<pollfd> _pollFds;
		std::map<int, irc::User *> _users;
		std::vector<irc::Channel> _channels;
		std::string _password;
		std::string _datatime;
		std::string _usrMode;
		std::string _chanMode;
		std::string	_oper_name;
		std::string	_oper_password;
		std::string _hostaddr;
		bool		_on;
		bool		_restart;

	public:
		Server(char *port, char *password);
		~Server();

		std::vector<irc::Channel *> getChannels();
		std::string getPassword();
		std::string getVersion();
		std::string getDatatime();
		std::map<int, User *> getUsers();
		std::string getUsrMode();
		std::string getChanMode();
		int getchanLimit();
		irc::User* getUserByNick(std::string nick);
		Channel* getChannelByName(std::string name);
		std::vector<irc::Channel *> getListChannelByName(std::vector<std::string> name);
		std::string getOperName() const;
		std::string getOperPassword() const;
		bool on(void) const;
		bool getRestart(void) const;
		void restart(char *a, char *b);

		void removeChan(std::string name);

		void setDatatime();
		void setPassword(std::string pass);
		void setSocketServer(int domain, int type, int protocol);

		void addSocket(int socket);
		void configSocketServer();
		void manipSocket(int fd, int cmd, int arg);
		void setAddressServer(char *port);
		void bindAddress();
		void listenAddress();

		void monitoring();
		void acceptClient();
		void monitoringClient();
		void runtime();

		void createChan(std::string name, irc::User* usr);
		void joinChan(irc::Channel* chan, irc::User* usr);
		void broadcast(std::string message);

		void DisplayError(std::string message)
		{
			std::cout << RED << message << STOP << std::endl;
			exit(1);
		}
		void deleteUser(int fd);
		void turnOff(void);
		void setRestart(bool x);
		std::string getHostaddr() const;
	};
}
#endif
