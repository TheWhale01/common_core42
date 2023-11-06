/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 15:09:42 by hubretec          #+#    #+#             */
/*   Updated: 2022/03/08 18:44:14 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include "mlx.h"
#include "libft.h"
#include "so_long.h"

void	set_starting_pos(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (game->map.map[++i])
	{
		j = -1;
		while (game->map.map[i][++j])
		{
			if (game->map.map[i][j] == game->player.value)
			{
				game->player.pos.x = j * game->map.assets.size;
				game->player.pos.y = i * game->map.assets.size;
			}
			if (game->map.map[i][j] == game->map.assets.collectible.value)
				game->nb_collectibles++;
		}			
	}
}

void	init_game(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		exit_msg(EXIT_FAILURE, "Could not load mlx.", game);
	game->map.assets.pos.x = 0;
	game->map.assets.pos.y = 0;
	game->mlx_win = mlx_new_window(game->mlx,
			game->map.assets.size * game->map.width,
			game->map.assets.size * game->map.height, "so_long");
	if (!game->mlx_win)
		exit_msg(EXIT_FAILURE, "Could not render window.", game);
}

void	init_img(t_img *img, char *path, char value)
{
	img->path = path;
	img->img = NULL;
	img->value = value;
}

void	init_assets(t_game *game)
{
	game->map.assets.size = 64;
	init_img(&(game->map.assets.exit), "./assets/exit.xpm", 'E');
	init_img(&(game->map.assets.wall), "./assets/wall.xpm", '1');
	init_img(&(game->map.assets.empty), "./assets/floor.xpm", '0');
	init_img(&(game->map.assets.collectible), "./assets/diamond.xpm", 'C');
	init_img(&(game->player.back), "./assets/player_B.xpm", 'P');
	init_img(&(game->player.left), "./assets/player_L.xpm", 'P');
	init_img(&(game->player.right), "./assets/player_R.xpm", 'P');
	init_img(&(game->player.front), "./assets/player_T.xpm", 'P');
	init_img(&(game->player.exit_front), "./assets/exit_T.xpm", 'P');
	init_img(&(game->player.exit_back), "./assets/exit_B.xpm", 'P');
	init_img(&(game->player.exit_left), "./assets/exit_L.xpm", 'P');
	init_img(&(game->player.exit_right), "./assets/exit_R.xpm", 'P');
	game->player.value = 'P';
	set_starting_pos(game);
}

void	init(char *filename, t_game *game)
{
	int	fd;

	game->nb_moves = 1;
	game->map.width = 0;
	game->nb_collectibles = 0;
	game->player.nb_collectibles = 0;
	fd = open(filename, O_RDWR | __O_NOFOLLOW);
	if (fd == -1)
		exit_msg(EXIT_FAILURE, "Could not open the file.", game);
	store_map(fd, &(game->map));
	if (!game->map.map)
		exit_msg(EXIT_FAILURE, "No map in file.", game);
	init_assets(game);
	game->map.height = tablen(game->map.map);
	check_map(game);
	init_game(game);
	create_img_ptr(game);
}
