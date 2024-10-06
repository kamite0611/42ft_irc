# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kai11 <kai11@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/31 21:29:27 by akamite           #+#    #+#              #
#    Updated: 2024/10/06 18:26:57 by kai11            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= ircserv
CC		= c++
FLAGS	= -std=c++98 #-Wall -Wextra -Werror

DEBUG_FLAG = -DDEBUG=1

OBJ_DIR	= objs/
SRC_DIR = src/

FILES	= \
	main \
	Server/Server \
	Server/Config/Config \
	Server/Display/Display \
	Server/Channel/Channel \
	User/User \
	User/Command/Command \
	User/Command/reply \
	User/Command/Connection/CAP \
	User/Command/Connection/PASS \
	User/Command/Connection/NICK \
	User/Command/Connection/USER \
	User/Command/Server/LUSERS \
	User/Command/Server/MOTD \
	Utils/Utils

DIRS = \
	Server/ \
	Server/Config/ \
	Server/Display/ \
	Server/Channel/ \
	User/ \
	User/Command/ \
	User/Command/Connection \
	User/Command/Server \
	Utils/

INC_DIRS = $(addprefix -I ./$(SRC_DIR), $(DIRS))
OBJ_DIRS = $(addprefix $(OBJ_DIR), $(DIRS))

SRCS	= $(addprefix $(SRC_DIR), $(FILES:=.cpp))
OBJS	= $(addprefix $(OBJ_DIR), $(FILES:=.o))
INCS	= \
	-I ./includes/ \
	$(INC_DIRS)


all: dirs $(NAME)

dirs:
	@mkdir -p $(OBJ_DIR) $(OBJ_DIRS)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(INCS) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	$(CC) $(FLAGS) -c $< -o $@ $(INCS)

clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

debug: INCS += $(DEBUG_FLAG)
debug: re
	./$(NAME) 6667 password

run: all
	./$(NAME) 6667 password

run_client:
	irssi -c localhost -w password

.PHONY: all clean fclean re
