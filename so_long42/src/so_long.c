/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:49:02 by hubretec          #+#    #+#             */
/*   Updated: 2022/03/08 18:34:35 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "mlx.h"
#include "libft.h"
#include "so_long.h"

void	win(t_game	*game)
{
	int	x_map;
	int	y_map;

	x_map = game->player.pos.x / game->map.assets.size;
	y_map = game->player.pos.y / game->map.assets.size;
	if (game->map.map[y_map][x_map] == game->map.assets.exit.value
		&& game->player.nb_collectibles == game->nb_collectibles)
		exit_msg(EXIT_SUCCESS, "You Won !", game);
}

int	quit_game(t_game *game)
{
	exit_msg(EXIT_SUCCESS, NULL, game);
	return (1);
}

int	do_event(int keycode, t_game *game)
{
	if (keycode == 65307)
		exit_msg(EXIT_SUCCESS, NULL, game);
	else if (keycode == 'w' || keycode == 'W' || keycode == 65362)
		move_up(game);
	else if (keycode == 's' || keycode == 'S' || keycode == 65364)
		move_down(game);
	else if (keycode == 'a' || keycode == 'A' || keycode == 65361)
		move_left(game);
	else if (keycode == 'd' || keycode == 'D' || keycode == 65363)
		move_right(game);
	return (1);
}
