NAME	= ircserv
CC		= c++
FLAGS	= -std=c++98 -Wall -Wextra -Werror

DEBUG_FLAG = -DDEBUG=1
CMD_DEBUG_FLAG = -DCMD_DEBUG=1

OBJ_DIR	= objs/
SRC_DIR = src/

FILES	= \
	main \
	Server/Server \
	Config/Config \
	Channel/Channel \
	User/User \
	Command/Command \
	Command/reply \
	Command/CAP \
	Command/PASS \
	Command/NICK \
	Command/USER \
	Command/QUIT \
	Command/MODE \
	Command/PING \
	Command/PONG \
	Command/LUSERS \
	Command/MOTD \
	Command/TOPIC \
	Command/INVITE \
	Command/JOIN \
	Command/KICK \
	Command/PRIVMSG \
	Utils/Utils

DIRS = \
	Server/ \
	Channel/ \
	Config/ \
	User/ \
	Command/ \
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

leak_run: all
	valgrind --leak-check=full ./$(NAME) 6667 pass

debug: INCS += $(DEBUG_FLAG)
debug: run

cmd_debug: INCS += $(CMD_DEBUG_FLAG)
cmd_debug: run

.PHONY: all clean fclean re run run_client debug cmd_debug
