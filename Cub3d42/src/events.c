/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrossett <jrossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 01:36:34 by jrossett          #+#    #+#             */
/*   Updated: 2022/10/26 01:36:34 by jrossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	do_event(int keycode, t_game *game)
{
	if (keycode == 65307)
		exit_game_v(game);
	else if (keycode == 'w' || keycode == 'W' || keycode == 65362)
		game->forward = 1;
	else if (keycode == 's' || keycode == 'S' || keycode == 65364)
		game->backward = 1;
	else if (keycode == 'a' || keycode == 'A')
		game->left = 1;
	else if (keycode == 'd' || keycode == 'D')
		game->right = 1;
	else if (keycode == 65363)
		game->t_right = 1;
	else if (keycode == 65361)
		game->t_left = 1;
	return (0);
}

int	stop_event(int keycode, t_game *game)
{
	if (keycode == 'w' || keycode == 'W' || keycode == 65362)
		game->forward = 0;
	else if (keycode == 's' || keycode == 'S' || keycode == 65364)
		game->backward = 0;
	else if (keycode == 'a' || keycode == 'A')
		game->left = 0;
	else if (keycode == 'd' || keycode == 'D')
		game->right = 0;
	else if (keycode == 65363)
		game->t_right = 0;
	else if (keycode == 65361)
		game->t_left = 0;
	return (0);
}
