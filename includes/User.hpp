/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravily <mravily@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 14:48:36 by mravily           #+#    #+#             */
//   Updated: 2022/07/13 18:04:17 by jiglesia         ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP

#include <string>
#include <string.h>
#include <vector>
#include <map>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <netdb.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <iostream>
#include <stdarg.h>
#include <cerrno> // errno
#include <cstdlib> // exit
#include <cstdio> // puts

#define BUFFER_SIZE 4096
#define CRLF "\r\n"

#include "Channel.hpp"
#include "Command.hpp"

namespace irc
{
	class Server;
	class Channel;
	class Command;
	enum stats
	{
		CONNECTED,
		AUTHENTICATED,
		REGISTERED,
		ONLINE,
		LEAVE,
		ERROR
	};

	class User
	{
		friend class Server;
		friend class Channel;

		public:
			typedef void (*cmd_funct)(irc::Server *, irc::User *, irc::Command *);
			typedef std::string (*rpl_funct)(irc::Server *srv, irc::User usr, irc::Channel *chan);

		private:
			Server *_server;
			int _fd;
			struct sockaddr_in _address;

			int			_mandatory:4;
			bool		_operator;
			stats 		_status;
			std::string _mode;
			std::string _nickname;
			std::string _username;
			std::string _realname;
			std::string _hostaddr;
			std::string _hostname;

			int			_chanLimit;

			std::vector<Command *> _cmds;

			std::map<int, rpl_funct> _rpl;
			std::map<std::string, cmd_funct> _funct;

			std::vector<std::string> _waitingSend;
		std::string _reason;
		public:
			User(irc::Server *srv, int socket, sockaddr_in address);
			~User();

		void setNickname(std::string nickname);
		void setUsername(std::string username);
		void setRealname(std::string realname);
		void setStatus(stats newStatus);
		void setHostname(std::string hostname);
		void setMode(std::string mode);
		void setReason(std::string trailer);
		void setBits(int index);

		int			getFd();
		stats		getStatus();
		irc::Server* getServer();
		std::string getMode();
		std::string getNickname();
		std::string getUsername();
		std::string getRealname();
		std::string getHostname();
		std::string getHostaddr();
		std::string getClient();
		std::string getReason();

		void addWaitingSend(std::string newReply);
		std::string printStatus();

		void setReplies();
		void setCmd();
		std::string getReplies(int code, irc::Channel *chan);
		void getMessages();
		void reply(int code, irc::Channel *chan = NULL);
		void registration();
		void processReply();
		void processCommand();
		void broadcast(irc::Channel *chan, std::string message, irc::User *without);
		void printUser();
		void DisplayError(std::string message)
		{
			int errn = errno;
			std::cout << message << strerror(errn) << std::endl;
			exit(1);
		}

	};
}

std::vector<std::string> split(std::string s, std::string delimiter);

void PASS(irc::Server *srv, irc::User *usr, irc::Command *cmd);
void NICK(irc::Server *srv, irc::User *usr, irc::Command *cmd);
void USER(irc::Server *srv, irc::User *usr, irc::Command *cmd);
void MODE(irc::Server *srv, irc::User *usr, irc::Command *cmd);
void PING(irc::Server *srv, irc::User *usr, irc::Command *cmd);
void JOIN(irc::Server *srv, irc::User *usr, irc::Command *cmd);
void QUIT(irc::Server *srv, irc::User *usr, irc::Command *cmd);
void PART(irc::Server *srv, irc::User *usr, irc::Command *cmd);
void PRIVMSG(irc::Server *srv, irc::User *usr, irc::Command *cmd);
void LIST(irc::Server *srv, irc::User *usr, irc::Command *cmd);
void TOPIC(irc::Server *srv, irc::User *usr, irc::Command *cmd);

#endif
