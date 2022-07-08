/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravily <mravily@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 15:42:04 by mravily           #+#    #+#             */
/*   Updated: 2022/07/07 19:17:22 by mravily          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

irc::Channel::Channel(bool type, std::string name, irc::User* ope, std::string pass) : _private(type), _name(name), _password(pass)
{
	_operator.push_back(ope);
}

irc::Channel::~Channel() {};