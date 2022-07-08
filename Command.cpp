/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravily <mravily@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 15:25:35 by mravily           #+#    #+#             */
/*   Updated: 2022/07/06 15:55:21 by mravily          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

std::string irc::Command::getPrefix() {return (_prefix);};
std::string irc::Command::getTrailer() {return (_trailer);};
std::vector<std::string> irc::Command::getParams() {return (_params);};

irc::Command::Command(std::string message) : _message(message)
{
	
	std::string delimiter(":");
	size_t position;
	if ((position = message.find(delimiter)) != std::string::npos)
	{
		std::string tmp = message.substr(0, position);
		message.erase(0, position + delimiter.length());
		_trailer = message;
		message = tmp;
	}
	
	_params = split(message, " ");
	_prefix = *(_params.begin());
	_params.erase(_params.begin());
	
	for (size_t index = 0; index < _prefix.length(); ++index)
		_prefix[index] = std::toupper(_prefix[index]);
	
	std::cout << "[CLIENT] Requête client (" << _prefix << ")" << std::endl;
	
	std::cout << "message: " << message << std::endl;
	std::cout << "Prefix: " << _prefix << std::endl;
	for (std::vector<std::string>::iterator it(_params.begin()); it != _params.end(); ++it)
		std::cout << "Params: " << (*it) << std::endl;
	std::cout << "trailer: " << _trailer << "\n" << std::endl;
}

irc::Command::~Command()
{
}