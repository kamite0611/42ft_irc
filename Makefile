# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akamite <akamite@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/31 21:29:27 by akamite           #+#    #+#              #
#    Updated: 2024/09/14 18:00:10 by akamite          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= ircserv
CC		= c++
FLAGS	= -std=c++98 #-Wall -Wextra -Werror

OBJ_DIR	= objs/
SRC_DIR = src/

FILES	= \
	main \
	Server/Server \
	Server/Config/Config \
	Server/Display/Display \
	User/User \
	Utils/Utils


SRCS	= $(addprefix $(SRC_DIR), $(FILES:=.cpp))
OBJS	= $(addprefix $(OBJ_DIR), $(FILES:=.o))
INCS	= \
	-I ./includes/ \
	-I ./src/Server/ \
	-I ./src/Server/Config/ \
	-I ./src/Server/Display/ \
	-I ./src/User/ \
	-I ./src/Utils/

all: dirs $(NAME)

dirs:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)Server/
	@mkdir -p $(OBJ_DIR)Server/Config/
	@mkdir -p $(OBJ_DIR)Server/Display/
	@mkdir -p $(OBJ_DIR)User/
	@mkdir -p $(OBJ_DIR)Utils/

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(INCS) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	$(CC) $(FLAGS) -c $< -o $@ $(INCS)

clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

debug: re
	./$(NAME)

run: all
	./$(NAME) 6667 password

.PHONY: all clean fclean re
