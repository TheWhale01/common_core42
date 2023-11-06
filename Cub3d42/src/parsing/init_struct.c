/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrossett <jrossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 01:35:39 by jrossett          #+#    #+#             */
/*   Updated: 2022/10/26 01:35:41 by jrossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_elem	*ft_init_elem(void)
{
	t_elem	*elem;

	elem = malloc(sizeof(t_elem) * 1);
	if (!elem)
		return (NULL);
	elem->no = NULL;
	elem->so = NULL;
	elem->we = NULL;
	elem->ea = NULL;
	elem->f = NULL;
	elem->c = NULL;
	elem->nb_elem = 0;
	elem->fr = 0;
	elem->fg = 0;
	elem->fb = 0;
	elem->cr = 0;
	elem->cg = 0;
	elem->cb = 0;
	elem->fcolor = 0;
	elem->ccolor = 0;
	return (elem);
}

void	ft_init_map(t_game *game)
{
	game->map = malloc(sizeof(t_map) * 1);
	if (!game->map)
		exit_game(game, ERR_MALLOC, -1);
	game->map->map = NULL;
	game->map->nb_player = 0;
	game->map->elem = ft_init_elem();
	if (!game->map->elem)
		exit_game(game, ERR_MALLOC, -1);
}

t_img	*init_img(void)
{
	t_img	*img;

	img = malloc(sizeof(t_img) * 1);
	if (!img)
		return (NULL);
	img->img = NULL;
	img->addr = NULL;
	return (img);
}

void	init_pos(t_game *game)
{
	game->player->pos = malloc(sizeof(t_pos) * 1);
	if (!game->player->pos)
		exit_game(game, ERR_MALLOC, -2);
	game->player->pos->x = 0;
	game->player->pos->y = 0;
}

void	init_player(t_game *game)
{
	game->player = malloc(sizeof(t_player) * 1);
	if (!game->player)
		exit_game(game, ERR_MALLOC, -2);
	init_pos(game);
	game->player->speed = 0.1f;
	game->player->player = 0;
}
