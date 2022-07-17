# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile.settings.mk                               :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mravily <mravily@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/21 21:06:11 by rotrojan          #+#    #+#              #
#    Updated: 2022/07/17 19:32:44 by mravily          ###   ########.fr        #
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
		CmdFunct.cpp \
		Command.cpp \
		main.cpp \
		Nick.cpp \
		Server.cpp \
		Users.cpp \
		Utils.cpp \
		MODE/MODE.cpp MODE/CHAN/modeChan.cpp MODE/USER/modeUser.cpp

# path of sources
PATH_SRCS = ./srcs

# pathe of includes
INCLUDES =	./includes/

# flags for compilation
CXXFLAGS = -Wall -Wextra -Werror# -std=c++98

# compiler used
CXX = c++
