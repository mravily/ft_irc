/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravily <mravily@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 15:19:17 by mravily           #+#    #+#             */
//   Updated: 2022/07/12 00:58:13 by jiglesia         ###   ########.fr       //
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

#include "Channel.hpp"
#include "User.hpp"

#define RPL_JOIN_ 011
#define RPL_MODE_ 012

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
		int 		_chanLimit;

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
		void joinChan(irc::Channel* chan, irc::User* usr, std::string password = "");

		void DisplayError(std::string message)
			{
				int errn = errno;
				std::cout << message << strerror(errn) << std::endl;
				exit(1);
			}
		void deleteUser(int fd);
	};
}
#endif
