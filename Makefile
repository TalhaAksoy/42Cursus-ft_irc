NAME = ircserv

SRC_FILES = main.cpp User.cpp utils.cpp Server.cpp Execute.cpp Channel.cpp
DESKTOP = ~/Desktop/
SRC_DIR = ./src/
OBJ_DIR = ./obj/
INC_DIR = ./inc/
BIN_DIR = ./bin/

OBJS = $(addprefix $(OBJ_DIR), $(SRC_FILES:.cpp=.o))

CC = g++

FLAGS = -Wall -Werror -Wextra

TEMP_FLAGS = -g

all:$(NAME)

test :
	echo $(OBJS)

$(NAME):$(OBJS)
	mkdir -p $(BIN_DIR)
	@$(CC) $(OBJS) -o $(BIN_DIR)$(NAME)
	@cp $(BIN_DIR)$(NAME) $(DESKTOP) 
	@echo "irc compiled. It is in $(BIN_DIR) directory and Desktop."

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@mkdir -p $(OBJ_DIR)
	@$(CC) -c $^ -o $@ -I $(INC_DIR)
	@echo "$@ compiled"

clean:
	@rm -f $(OBJS)
	@rm -rf $(OBJ_DIR)
	@echo Obj files cleaned.

fclean: clean
	@rm -rf $(BIN_DIR)
	@rm -rf $(DESKTOP)$(NAME)
	@echo Program deleted.

re: fclean $(NAME) clean