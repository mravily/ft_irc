/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravily <mravily@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 15:21:57 by mravily           #+#    #+#             */
/*   Updated: 2022/07/13 17:00:29 by nayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <string>
#include <vector>
#include <iostream>
#include <sstream>

#include "User.hpp"

namespace irc
{
	class User;
	
	class Channel
	{
		friend class User;
		
		private:
			bool 				_private;
			std::string			_name;
			std::string			_mode;
			std::string			_password;
			std::string			_topic;
			std::string			_topicDate;
			std::vector<irc::User *> _users;
			std::vector<irc::User *> _operator;
			std::vector<std::string> _listBan;
			std::string			_datatime;
			int					_capacity;
			std::string			_lastTry;
			// int test;
			
		public:
			Channel(bool type, std::string name, irc::User* ope, std::string password = "");
			~Channel();

			std::string getName() {return (_name);};
			std::string getModes() {return (_mode);};
			bool 		getMode(char toFind) {return (_mode.find(toFind));};
			bool		isPrivate() {return (this->_private);}
			std::string getPassword() {return (_password);};
			std::string getListUsers();
			std::string getDatatime() {return (_datatime);};
			int			getCapacity() {return (_capacity);};
			std::string getLastTry() {return (_lastTry);};
			std::string getTopic() {return (_topic);}
			std::vector<User *> getUser() {return (_users);};
			std::vector<User *> getOperator() {return (_operator);};
			std::vector<User *> getUsers();
			std::string getUserSize();
			std::string getCurrentDate();
			std::string getDate() {return (this->_datatime);}
			void setLastTry(std::string value) {this->_lastTry = value;};
			void setDateTopic() {this->_topicDate = getCurrentDate();}
			void setTopic(std::string newTopic) {setDateTopic(); this->_topic = newTopic;}
			void addUser(irc::User* usr);
			void removeUser(irc::User* usr, std::string message);
			bool knowUser(irc::User* usr);
	};
}
#endif
