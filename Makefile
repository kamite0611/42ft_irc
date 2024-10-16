NAME	= ircserv
CC		= c++
FLAGS	= -std=c++98 #-Wall -Wextra -Werror

DEBUG_FLAG = -DDEBUG=1
CMD_DEBUG_FLAG = -DCMD_DEBUG=1

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
	User/Command/Connection/QUIT \
	User/Command/Connection/MODE \
	User/Command/Connection/PING \
	User/Command/Connection/PONG \
	User/Command/Server/LUSERS \
	User/Command/Server/MOTD \
	User/Command/Channel/TOPIC \
	User/Command/Channel/INVITE \
	User/Command/Channel/JOIN \
	User/Command/Channel/KICK \
	User/Command/Channel/PRIVMSG \
	Utils/Utils

DIRS = \
	Server/ \
	Server/Channel/ \
	Server/Config/ \
	Server/Display/ \
	User/ \
	User/Command/ \
	User/Command/Connection \
	User/Command/Server \
	User/Command/Channel \
	Utils/

INC_DIRS = $(addprefix -I ./$(SRC_DIR), $(DIRS))
OBJ_DIRS = $(addprefix $(OBJ_DIR), $(DIRS))

SRCS	= $(addprefix $(SRC_DIR), $(FILES:=.cpp))
OBJS	= $(addprefix $(OBJ_DIR), $(FILES:=.o))
INCS	= \
	-I ./includes/ \
	$(INC_DIRS)

OSNAME := $(shell uname -s)
ifeq ($(OSNAME), Darwin)
	INCS += -DIS_MAC=true
endif


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

run: all
	./$(NAME) 6667 pass

run_client:
	irssi -c localhost -w pass -p 6667 -n DebugUser

debug: INCS += $(DEBUG_FLAG)
debug: run

cmd_debug: INCS += $(CMD_DEBUG_FLAG)
cmd_debug: run

.PHONY: all clean fclean re run run_client debug cmd_debug
