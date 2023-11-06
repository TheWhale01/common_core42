CC=gcc
BIN_DIR=bin/
OBJ_DIR=obj/
SRC_DIR=src/
INCLUDES=includes/
CFLAGS=-Wall -Wextra -Werror -I $(INCLUDES)
NAME=$(BIN_DIR)pipex
NAME_BONUS=$(BIN_DIR)pipex_bonus

CFILES=$(addprefix $(SRC_DIR), main.c utils.c pipex.c utils/ft_putendl_fd.c utils/ft_putstr.c \
utils/ft_split.c utils/ft_strchr.c utils/ft_strdup.c utils/ft_strjoin.c utils/ft_strlen.c \
utils/ft_strncmp.c utils/get_next_line.c)
CFILES_BONUS=$(addprefix $(SRC_DIR), main_bonus.c utils.c pipex.c utils/ft_putendl_fd.c utils/ft_putstr.c \
utils/ft_split.c utils/ft_strchr.c utils/ft_strdup.c utils/ft_strjoin.c utils/ft_strlen.c \
utils/ft_strncmp.c utils/get_next_line.c)
OBJS=$(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(CFILES))
OBJS_BONUS=$(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(CFILES_BONUS))

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@if [ ! -d "$(dir $@)" ]; then mkdir -p $(dir $@); fi
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@if [ ! -d "$(BIN_DIR)" ]; then mkdir $(dir $@); fi
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

bonus: $(NAME) $(OBJS_BONUS)
	@if [ ! -d "$(BIN_DIR)" ]; then mkdir $(dir $@); fi
	$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(NAME_BONUS)

bonus_debug: CFLAGS=-Wall -Wextra -Werror -I $(INCLUDES) -g
bonus_debug: bonus

debug: CFLAGS=-Wall -Wextra -Werror -I $(INCLUDES) -g
debug: $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(BIN_DIR)

sanitize:CFLAGS=-Wall -Wextra -Werror -I $(INCLUDES) -fsanitize=address
sanitize: $(NAME)

re: fclean all

re_bonus: fclean bonus

re_debug: fclean debug

re_sanitize: fclean sanitize

.PHONY: all bonus debug clean fclean re sanitize re_debug re_sanitize \
re_bonus bonus_debug