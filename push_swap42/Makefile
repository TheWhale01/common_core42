CC=gcc
BIN_DIR=bin/
OBJ_DIR=obj/
LIBFT_DIR=libft/
INCLUDES=includes/
COMMON_DIR=../common/
CFLAGS=-Wall -Wextra -Werror -I $(INCLUDES)

#push_swap files
SRC_DIR_PUSH_SWAP=src/push_swap/
OBJ_DIR_PUSH_SWAP=obj/push_swap/
CFILES_PUSH_SWAP=$(addprefix $(SRC_DIR_PUSH_SWAP), main.c solver.c med.c cost.c \
simple_sort.c $(COMMON_DIR)s.c $(COMMON_DIR)p.c $(COMMON_DIR)r.c $(COMMON_DIR)rr.c \
$(COMMON_DIR)check.c $(COMMON_DIR)stack.c $(COMMON_DIR)utils.c $(COMMON_DIR)pop.c)
OBJS=$(patsubst $(SRC_DIR_PUSH_SWAP)%.c, $(OBJ_DIR_PUSH_SWAP)%.o, $(CFILES_PUSH_SWAP))
NAME_PUSH_SWAP=$(BIN_DIR)push_swap

#checker files
CHECKER_SRC_DIR=src/checker/
CHECKER_OBJ_DIR=obj/checker/
CFILES_CHECKER=$(addprefix $(CHECKER_SRC_DIR), main.c checker.c  $(COMMON_DIR)check.c \
$(COMMON_DIR)stack.c $(COMMON_DIR)utils.c $(COMMON_DIR)pop.c $(COMMON_DIR)s.c \
$(COMMON_DIR)p.c $(COMMON_DIR)r.c $(COMMON_DIR)rr.c)
OBJS_CHECKER=$(patsubst $(CHECKER_SRC_DIR)%.c, $(CHECKER_OBJ_DIR)%.o, $(CFILES_CHECKER))
NAME_CHECKER=$(BIN_DIR)checker

$(OBJ_DIR_PUSH_SWAP)%.o: $(SRC_DIR_PUSH_SWAP)%.c
	@if [ ! -d "$(dir $@)" ]; then mkdir -p $(dir $@); fi
	$(CC) $(CFLAGS) -c $< -o $@

$(CHECKER_OBJ_DIR)%.o: $(CHECKER_SRC_DIR)%.c
	@if [ ! -d "$(dir $@)" ]; then mkdir -p $(dir $@); fi
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME_PUSH_SWAP): $(OBJS)
	@if [ ! -d "./$(BIN_DIR)" ]; then mkdir $(dir $@); fi
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME_PUSH_SWAP) -L ./$(LIBFT_DIR)bin/ -lft

$(NAME_CHECKER): $(OBJS_CHECKER)
	@if [ ! -d "./$(BIN_DIR)" ]; then mkdir $(dir $@); fi
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJS_CHECKER) -o $(NAME_CHECKER) -L ./$(LIBFT_DIR)bin/ -lft

all: $(NAME_PUSH_SWAP)

checker: $(NAME_PUSH_SWAP) $(NAME_CHECKER)

checker_debug: CFLAGS=-Wall -Wextra -Werror -I $(INCLUDES) -g
checker_debug: checker

debug: CFLAGS=-Wall -Wextra -Werror -I $(INCLUDES) -g
debug: $(NAME_PUSH_SWAP)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(BIN_DIR)
	$(MAKE) fclean -C $(LIBFT_DIR)

sanitize:CFLAGS=-Wall -Wextra -Werror -I $(INCLUDES) -fsanitize=address
sanitize: $(NAME_PUSH_SWAP)

re: fclean all

re_checker: fclean checker

re_debug: fclean debug

re_sanitize: fclean sanitize

.PHONY: all checker debug clean fclean sanitize re_checker re_debug re_sanitize
