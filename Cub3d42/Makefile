CC=gcc
NAME=cub3D
OBJ_DIR=obj/
SRC_DIR=src/
MLX_DIR=minilibx/
INCLUDES=includes/
HEADER= $(INCLUDES)cub3d.h $(INCLUDES)libft.h
MLX_FLAGS=-L./$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm
CFLAGS=-Wall -Wextra -Werror -I $(INCLUDES) -lXext -lX11 -lm -L minilibx/ -lmlx_Linux -Ofast -flto
CFILES=$(addprefix $(SRC_DIR), main.c parsing/parsing.c parsing/init_struct.c parsing/parsing_map.c\
		parsing/name_map.c parsing/parsing_elem.c parsing/parsing_utils.c parsing/verif_valid_map.c\
		parsing/free_utils.c mlx_utils.c map.c events.c moves.c parsing/init_struct2.c raycasting.c)
OBJS=$(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(CFILES))

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@if [ ! -d "$(dir $@)" ]; then mkdir -p $(dir $@); fi
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(HEADER) $(OBJS)
	$(MAKE) -C libft/
	$(MAKE) -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(OBJS) libft/bin/libft.a -o $(NAME) $(MLX_FLAGS)

all: $(NAME)

clean:
	$(MAKE) clean -C libft/
	$(MAKE) clean -C $(MLX_DIR)
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf libft/bin/libft.a
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
