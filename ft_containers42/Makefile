CC=clang++
OBJ_DIR=obj/
SRC_DIR=src/
BIN_DIR=bin/
INCLUDES=includes/
NAME=$(BIN_DIR)containers
NAME_STD=$(BIN_DIR)std
CFLAGS=-Wall -Wextra -Werror -I $(INCLUDES) -g -std=c++98
CFILES=$(addprefix $(SRC_DIR), main.cpp 42test.cpp vect_tests.cpp map_tests.cpp stack_test.cpp)
OBJS=$(patsubst $(SRC_DIR)%.cpp, $(OBJ_DIR)%.o, $(CFILES))

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@if [ ! -d "$(dir $@)" ]; then mkdir -p $(dir $@); fi
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@if [ ! -d "$(dir $@)" ]; then mkdir -p $(dir $@); fi
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

std: NAME=$(NAME_STD)
std: fclean
std: CFLAGS=-Wall -Wextra -Werror -I $(INCLUDES) -g -std=c++98 -D NM=std
std: $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)
	rm -rf $(NAME_STD)

re: fclean all

.PHONY: all debug clean fclean re
