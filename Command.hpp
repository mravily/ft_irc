/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravily <mravily@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 15:19:02 by mravily           #+#    #+#             */
/*   Updated: 2022/06/27 19:47:32 by mravily          ###   ########.fr       */
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
			std::string _prefix;
			std::vector<std::string> _params;
			std::string _trailer;
			std::string _message;
		public:
			Command(std::string message);
			~Command();

			std::string getPrefix();
			std::string getTrailer();
			std::vector<std::string> getParams();
	};
}
#endif