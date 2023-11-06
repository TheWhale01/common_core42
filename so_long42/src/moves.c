/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 09:37:20 by hubretec          #+#    #+#             */
/*   Updated: 2022/03/08 18:57:51 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft.h"
#include "so_long.h"

void	draw_exit(t_game *game, t_pos prev_pos, int x_map, int y_map)
{
	if (game->map.map[y_map][x_map] == game->map.assets.exit.value)
		mlx_put_image_to_window(game->mlx, game->mlx_win,
			game->map.assets.exit.img, prev_pos.x, prev_pos.y);
	else
		mlx_put_image_to_window(game->mlx, game->mlx_win,
			game->map.assets.empty.img, prev_pos.x, prev_pos.y);
}

void	move_up(t_game *game)
{
	int		x_map;
	int		y_map;
	t_pos	prev_pos;

	x_map = game->player.pos.x / game->map.assets.size;
	y_map = (game->player.pos.y / game->map.assets.size);
	if (game->map.map[y_map - 1][x_map] == game->map.assets.wall.value)
		return ;
	else if (game->map.map[y_map][x_map] == game->map.assets.collectible.value)
	{
		game->player.nb_collectibles++;
		game->map.map[y_map][x_map] = game->map.assets.empty.value;
	}
	ft_printf("%d\n", game->nb_moves++);
	prev_pos = game->player.pos;
	game->player.pos.y -= game->map.assets.size;
	if (game->map.map[y_map - 1][x_map] == game->map.assets.exit.value)
		mlx_put_image_to_window(game->mlx, game->mlx_win,
			game->player.exit_front.img,
			game->player.pos.x, game->player.pos.y);
	else
		mlx_put_image_to_window(game->mlx, game->mlx_win,
			game->player.front.img, game->player.pos.x, game->player.pos.y);
	draw_exit(game, prev_pos, x_map, y_map);
	win(game);
}

void	move_down(t_game *game)
{
	int		x_map;
	int		y_map;
	t_pos	prev_pos;

	x_map = game->player.pos.x / game->map.assets.size;
	y_map = (game->player.pos.y / game->map.assets.size);
	if (game->map.map[y_map + 1][x_map] == game->map.assets.wall.value)
		return ;
	else if (game->map.map[y_map][x_map] == game->map.assets.collectible.value)
	{
		game->player.nb_collectibles++;
		game->map.map[y_map][x_map] = game->map.assets.empty.value;
	}
	ft_printf("%d\n", game->nb_moves++);
	prev_pos = game->player.pos;
	game->player.pos.y += game->map.assets.size;
	if (game->map.map[y_map + 1][x_map] == game->map.assets.exit.value)
		mlx_put_image_to_window(game->mlx, game->mlx_win,
			game->player.exit_back.img,
			game->player.pos.x, game->player.pos.y);
	else
		mlx_put_image_to_window(game->mlx, game->mlx_win,
			game->player.back.img, game->player.pos.x, game->player.pos.y);
	draw_exit(game, prev_pos, x_map, y_map);
	win(game);
}

void	move_left(t_game *game)
{
	int		x_map;
	int		y_map;
	t_pos	prev_pos;

	x_map = game->player.pos.x / game->map.assets.size;
	y_map = game->player.pos.y / game->map.assets.size;
	if (game->map.map[y_map][x_map - 1] == game->map.assets.wall.value)
		return ;
	else if (game->map.map[y_map][x_map] == game->map.assets.collectible.value)
	{
		game->player.nb_collectibles++;
		game->map.map[y_map][x_map] = game->map.assets.empty.value;
	}
	ft_printf("%d\n", game->nb_moves++);
	prev_pos = game->player.pos;
	game->player.pos.x -= game->map.assets.size;
	if (game->map.map[y_map][x_map - 1] == game->map.assets.exit.value)
		mlx_put_image_to_window(game->mlx, game->mlx_win,
			game->player.exit_left.img,
			game->player.pos.x, game->player.pos.y);
	else
		mlx_put_image_to_window(game->mlx, game->mlx_win,
			game->player.left.img, game->player.pos.x, game->player.pos.y);
	draw_exit(game, prev_pos, x_map, y_map);
	win(game);
}

void	move_right(t_game *game)
{
	int		x_map;
	int		y_map;
	t_pos	prev_pos;

	x_map = game->player.pos.x / game->map.assets.size;
	y_map = game->player.pos.y / game->map.assets.size;
	if (game->map.map[y_map][x_map + 1] == game->map.assets.wall.value)
		return ;
	else if (game->map.map[y_map][x_map] == game->map.assets.collectible.value)
	{
		game->player.nb_collectibles++;
		game->map.map[y_map][x_map] = game->map.assets.empty.value;
	}
	ft_printf("%d\n", game->nb_moves++);
	prev_pos = game->player.pos;
	game->player.pos.x += game->map.assets.size;
	if (game->map.map[y_map][x_map + 1] == game->map.assets.exit.value)
		mlx_put_image_to_window(game->mlx, game->mlx_win,
			game->player.exit_right.img,
			game->player.pos.x, game->player.pos.y);
	else
		mlx_put_image_to_window(game->mlx, game->mlx_win,
			game->player.right.img, game->player.pos.x, game->player.pos.y);
	draw_exit(game, prev_pos, x_map, y_map);
	win(game);
}
