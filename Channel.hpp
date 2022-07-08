/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravily <mravily@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 15:21:57 by mravily           #+#    #+#             */
/*   Updated: 2022/07/07 19:36:59 by mravily          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "User.hpp"

#include <string>
#include <vector>

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
			std::string			_datatime;
	
			
		public:
			Channel(bool type, std::string name, irc::User* ope, std::string password = "");
			~Channel();

			std::string getName() {return (_name);};
			
			// addUser();
			// removeUser();
	};
}
#endif