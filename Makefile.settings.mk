# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile.settings.mk                               :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mravily <mravily@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/21 21:06:11 by mravily           #+#    #+#              #
#    Updated: 2022/07/20 09:56:53 by mravily          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# The name of the binary
NAME = ircserv

# Port to host the server
PORT = 6667

# Password for the server
PSWD = test

# sources needed to compile
SRC =	Channel.cpp \
		Command.cpp \
		main.cpp \
		Server.cpp \
		Users.cpp \
		Utils.cpp \
		messages/cmdOper/INVITE.cpp \
		messages/cmdOper/KICK.cpp \
		messages/cmdOper/KILL.cpp \
		messages/cmdOper/RESTART.cpp \
		messages/cmdOper/SQUIT.cpp \
		messages/cmdUser/JOIN.cpp \
		messages/cmdUser/LIST.cpp \
		messages/cmdUser/MODE.cpp \
		messages/cmdUser/NAMES.cpp \
		messages/cmdUser/OPER.cpp \
		messages/cmdUser/PART.cpp \
		messages/cmdUser/PING.cpp \
		messages/cmdUser/PRIVMSG.cpp \
		messages/cmdUser/QUIT.cpp \
		messages/cmdUser/TOPIC.cpp \
		messages/registration/NICK.cpp \
		messages/registration/PASS.cpp \
		messages/registration/USER.cpp \
		messages/cmdUser/mode/chan/modeChan.cpp \
		messages/cmdUser/mode/user/modeUser.cpp 

		

# path of sources
PATH_SRCS = ./srcs

# pathe of includes
INCLUDES =	./includes/

# flags for compilation
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

# compiler used
CXX = c++
