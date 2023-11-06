/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:56:18 by hubretec          #+#    #+#             */
/*   Updated: 2022/03/23 13:42:17 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "mlx.h"
#include "libft.h"
#include "so_long.h"

void	store_map(int fd, t_map *map)
{
	char	*line;

	map->map = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		map->map = add_line(map->map, line);
		if (!map->width)
			map->width = ft_strlen(line);
	}
	close(fd);
}

void	check_assets(t_game *game)
{
	int	nb_players;

	nb_players = is_in(game->map.map, game->player.value);
	if (!is_in(game->map.map, game->map.assets.collectible.value))
		exit_msg(EXIT_FAILURE, "Invalid map: Missing collectibles.", game);
	if (!is_in(game->map.map, game->map.assets.exit.value))
		exit_msg(EXIT_FAILURE, "Invalid map: Missing exit.", game);
	if (!is_in(game->map.map, game->map.assets.wall.value))
		exit_msg(EXIT_FAILURE, "Invalid map: Missing walls.", game);
	if (!nb_players)
		exit_msg(EXIT_FAILURE,
			"Invalid map: Missing player starting pos.", game);
	if (nb_players > 1)
		exit_msg(EXIT_FAILURE,
			"Invalid map: Too many player starting pos.", game);
}

void	check_map(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	check_assets(game);
	while (game->map.map[++i])
	{
		j = -1;
		if (ft_strlen(game->map.map[i]) != (size_t)game->map.width)
			exit_msg(EXIT_FAILURE, "Invalid map: Not a rectangle.", game);
		while (game->map.map[i][++j])
		{
			if ((!(i % (game->map.height - 1)) || !(j % (game->map.width - 1)))
				&& game->map.map[i][j] != game->map.assets.wall.value)
				exit_msg(EXIT_FAILURE, "Invalid map: Missing border.", game);
			if (game->map.map[i][j] != game->map.assets.collectible.value
				&& game->map.map[i][j] != game->map.assets.empty.value
				&& game->map.map[i][j] != game->map.assets.exit.value
				&& game->map.map[i][j] != game->map.assets.wall.value
				&& game->map.map[i][j] != game->player.value)
				exit_msg(EXIT_FAILURE, "Invalid map: Unknown character.", game);
		}
	}
}

void	check(int ac, char **av, t_game *game)
{
	game->mlx = NULL;
	game->mlx_win = NULL;
	game->map.map = NULL;
	if (ac != 2)
		exit_msg(EXIT_FAILURE, "Wrong number of args.", game);
	if (!ft_strcmp(&av[1][ft_strlen(av[1]) - 5], "/.ber")
		|| !ft_strcmp(av[1], ".ber")
		|| ft_strcmp(&av[1][ft_strlen(av[1]) - 4], ".ber"))
		exit_msg(EXIT_FAILURE, "Invalid filename: <filename>.ber", game);
	init(av[1], game);
}
