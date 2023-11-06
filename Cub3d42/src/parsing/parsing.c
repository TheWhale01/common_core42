/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrossett <jrossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 01:36:21 by jrossett          #+#    #+#             */
/*   Updated: 2022/10/26 01:36:21 by jrossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_all_space(t_map *map, int i)
{
	size_t	j;

	j = 0;
	while (map->map[i][j])
	{
		if (map->map[i][j] != ' ')
			return (0);
		j++;
	}
	return (1);
}

int	ft_first_last(t_map *map, t_player *player, int j)
{
	int	i;

	i = 0;
	while (map->map[j][i])
	{
		if (map->map[j][i] == '0' || map->map[j][i] == player->player)
			return (1);
		if (map->map[j][i] == '1')
			map->map[j][i] = 'm';
		i++;
	}
	i = -1;
	while (map->map[++i])
	{
		j = 0;
		if (ft_all_space(map, i))
			continue ;
		while (map->map[i][j] == ' ')
			j++;
		if (map->map[i][j] != '1' && map->map[i][j] != 'm')
			return (1);
		map->map[i][j] = 'm';
	}
	return (0);
}

int	ft_verif_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (game->map->map[i])
		i++;
	i--;
	while (game->map->map[j] && ft_all_space(game->map, j))
		j++;
	while (game->map->map[i] && ft_all_space(game->map, i))
		i--;
	if (!game->map->map[j] || !game->map->map[i])
		return (1);
	if (ft_first_last(game->map, game->player, j)
		|| ft_first_last(game->map, game->player, i))
		return (1);
	if (ft_mid_map(game))
		return (1);
	return (0);
}

t_game	*init_game(int fd)
{
	int		i;
	t_game	*game;

	i = -1;
	game = malloc(sizeof(t_game) * 1);
	if (!game)
	{
		close(fd);
		exit_game(game, ERR_MALLOC, -1);
	}
	game->img = NULL;
	game->map = NULL;
	game->fd = fd;
	game->mlx = NULL;
	game->mlx_win = NULL;
	game->ray = NULL;
	game->renderer = NULL;
	ft_init_map(game);
	game->img = malloc(sizeof(t_img) * 5);
	if (!game->img)
		exit_game(game, ERR_MALLOC, -1);
	ft_ver_img(i, game);
	init_player(game);
	return (game);
}

t_game	*ft_parsing(int ac, char **av)
{
	int		fd;
	t_game	*game;

	fd = ft_verif_name(ac, av);
	game = init_game(fd);
	if (ft_parse_elem(fd, game->map->elem) || ft_verif_elem(game->map->elem))
		exit_game(game, ERR_ELEM, -1);
	game->map->map = ft_parse_map(fd, game->map, game->player);
	if (!game->map->map)
		exit_game(game, ERR_MAP, -1);
	if (ft_verif_map(game))
		exit_game(game, ERR_MAP, -1);
	ft_color(game->map->elem);
	return (game);
}
