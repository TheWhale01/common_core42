CC=c++
NAME=form
OBJ_DIR=obj/
SRC_DIR=src/
INCLUDES=includes/
CFLAGS=-Wall -Wextra -Werror -I $(INCLUDES) -g -std=c++98
CFILES=$(addprefix $(SRC_DIR), main.cpp AForm.cpp Bureaucrat.cpp ShrubberyCreationForm.cpp \
	RobotomyRequestForm.cpp PresidentialPardonForm.cpp)
OBJS=$(patsubst $(SRC_DIR)%.cpp, $(OBJ_DIR)%.o, $(CFILES))

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@if [ ! -d "$(dir $@)" ]; then mkdir -p $(dir $@); fi
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all debug clean fclean re
