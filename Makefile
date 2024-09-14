# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akamite <akamite@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/31 21:29:27 by akamite           #+#    #+#              #
#    Updated: 2024/09/14 19:08:32 by akamite          ###   ########.fr        #
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

DIRS = \
	Server/ \
	Server/Config/ \
	Server/Display/ \
	User/ \
	Utils/

INC_DIRS = $(addprefix -I ./$(SRC_DIR), $(DIRS))
OBJ_DIRS = $(addprefix $(OBJ_DIR), $(DIRS))

SRCS	= $(addprefix $(SRC_DIR), $(FILES:=.cpp))
OBJS	= $(addprefix $(OBJ_DIR), $(FILES:=.o))
INCS	= \
	-I ./includes/ \
	$(INC_DIRS)

echo:
	echo $(INC_SRC_DIRS)

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

debug: re
	./$(NAME)

run: all
	./$(NAME) 6667 password

run_client:
	irssi -c localhost -w password

.PHONY: all clean fclean re
