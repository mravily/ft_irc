/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravily <mravily@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 15:19:17 by mravily           #+#    #+#             */
/*   Updated: 2022/07/08 19:17:52 by mravily          ###   ########.fr       */
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

#include "User.hpp"
#include "Channel.hpp"

namespace irc
{
	class User;
	
	class Server
	{
		private:
			std::string _version;
			int _socketServer;
			struct sockaddr_in _addrServer;
			std::vector<pollfd> _pollFds;
			std::map<int, User *> _users;
			std::vector<Channel> _channels;
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
			
			void createChan(std::vector<std::string> infos, irc::User* usr);
			void DisplayError(std::string message)
			{
				int errn = errno;
				std::cout << message << strerror(errn) << std::endl;
				exit(1);
			}
	};

	
}
#endif