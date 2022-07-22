/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravily <mravily@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 15:19:02 by mravily           #+#    #+#             */
/*   Updated: 2022/07/22 15:03:02 by mravily          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>
#include <vector>
#include <iostream>

std::vector<std::string> split(std::string s, std::string delimiter);

namespace irc
{
	class Command
	{
		private:
			std::string _message;
			std::string _prefix;
			std::vector<std::string> _params;
			std::string _trailer;
			bool		_unset;
		public:
			Command(std::string message);
			~Command();

			std::string getPrefix();
			std::string getTrailer();
			std::vector<std::string> getParams();
			bool		getUnset() {return _unset;};

			void		setTrailer(std::string trailer) {_trailer = trailer;};
	};
}
#endif