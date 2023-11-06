/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrossett <jrossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 01:35:54 by jrossett          #+#    #+#             */
/*   Updated: 2022/10/26 01:35:55 by jrossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_verif_img(t_game *game)
{
	int	i;

	i = 0;
	while (++i < 5)
	{
		if (!game->img[i]->img)
			exit_game(game, ERR_IMG, -1);
		game->img[i]->addr = mlx_get_data_addr(game->img[i]->img,
				&game->img[i]->bpp, &game->img[i]->len, &game->img[i]->endian);
		if (!game->img[i]->addr)
			exit_game(game, ERR_ADDR, -1);
	}
}

void	ft_create_img(t_game *game)
{
	int	var;

	var = 128;
	game->img[0]->img = mlx_new_image(game->mlx, L, H);
	if (!game->img[0]->img)
		exit_game(game, ERR_IMG, -1);
	game->img[0]->addr = mlx_get_data_addr(game->img[0]->img,
			&game->img[0]->bpp, &game->img[0]->len, &game->img[0]->endian);
	if (!game->img[0]->addr)
		exit_game(game, ERR_ADDR, -1);
	game->img[1]->img = mlx_xpm_file_to_image(game->mlx,
			game->map->elem->no, &var, &var);
	game->img[2]->img = mlx_xpm_file_to_image(game->mlx,
			game->map->elem->ea, &var, &var);
	game->img[3]->img = mlx_xpm_file_to_image(game->mlx,
			game->map->elem->so, &var, &var);
	game->img[4]->img = mlx_xpm_file_to_image(game->mlx,
			game->map->elem->we, &var, &var);
	ft_verif_img(game);
}

void	ft_color(t_elem *elem)
{
	elem->ccolor = (elem->cr << 16) + (elem->cg << 8) + elem->cb;
	elem->fcolor = (elem->fr << 16) + (elem->fg << 8) + elem->fb;
}

void	ft_perror(char *error)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}

int	ft_verif_name(int ac, char **av)
{
	int		i;
	char	*name;

	if (ac != 2)
		ft_perror(ERR_ARGS);
	name = av[1];
	i = ft_strlen(name);
	if (i == 4 || (i == 5 && name[0] == '.' && name[1] == '.')
		|| !ft_strnstr(name + (i - 4), ".cub", 4))
		ft_perror(ERR_NAME);
	i = open(name, __O_DIRECTORY);
	if (i > 0)
	{
		close(i);
		ft_perror(ERR_DIR);
	}
	i = open(name, O_RDONLY | __O_NOFOLLOW);
	if (i == -1)
		ft_perror(ERR_FILE);
	return (i);
}
