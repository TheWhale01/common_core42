/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_valid_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrossett <jrossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 01:36:26 by jrossett          #+#    #+#             */
/*   Updated: 2022/10/26 01:36:29 by jrossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_ver_img(int i, t_game *game)
{
	while (++i < 5)
	{
		game->img[i] = init_img();
		if (!game->img[i])
			exit_game(game, ERR_MALLOC, i);
	}
}

int	ft_exist_tab(t_map *map, size_t x, size_t y)
{
	if ((ft_strlen(map->map[x - 1]) - 1) < y
		|| (ft_strlen(map->map[x + 1]) - 1) < y)
		return (1);
	return (0);
}

void	ft_create_wall(t_map *map, size_t x, size_t y)
{
	if (ft_exist_tab(map, x, y))
		map->map[x][y] = 'm';
	else if (map->map[x - 1][y] == ' ' || map->map[x + 1][y] == ' '
		|| map->map[x][y - 1] == ' ' || map->map[x][y + 1] == ' ')
		map->map[x][y] = 'm';
}

int	ft_open_map(t_game *game, size_t x, size_t y)
{
	size_t	i;

	i = tablen(game->map->map);
	if (x == 0 || x == (i - 1) || y == 0
		|| y == ft_strlen(game->map->map[x]) - 1)
	{
		if (game->map->map[x][y] == '0'
			|| game->map->map[x][y] == game->player->player)
			return (1);
		return (0);
	}
	if (game->map->map[x][y] == '1' || game->map->map[x][y] == 'm')
		ft_create_wall(game->map, x, y);
	else if (game->map->map[x][y] == '0'
		|| game->map->map[x][y] == game->player->player)
	{
		if (ft_exist_tab(game->map, x, y))
			return (1);
		if (game->map->map[x - 1][y] == ' ' || game->map->map[x + 1][y] == ' '
			|| game->map->map[x][y - 1] == ' '
			|| game->map->map[x][y + 1] == ' ')
			return (1);
	}
	return (0);
}

int	ft_mid_map(t_game *game)
{
	size_t	x;
	size_t	y;

	x = 0;
	while (game->map->map[x])
	{
		y = 0;
		while (game->map->map[x][y])
		{
			if (ft_open_map(game, x, y))
				return (1);
			if (game->map->map[x][y] == game->player->player)
			{
				game->player->pos->x = y;
				game->player->pos->y = x;
			}
			y++;
		}
		if (game->map->map[x][y - 1] == '1')
			game->map->map[x][y - 1] = 'm';
		x++;
	}
	return (0);
}
