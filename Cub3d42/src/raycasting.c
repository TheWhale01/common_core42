/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrossett <jrossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 01:37:08 by jrossett          #+#    #+#             */
/*   Updated: 2022/10/26 01:37:09 by jrossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_renderer(int column, t_game *game)
{
	game->renderer->camerax = 2 * (double)column / (double)L - 1.0;
	game->renderer->raydirx = game->ray->dirx + game->ray->planex
		* game->renderer->camerax;
	game->renderer->raydiry = game->ray->diry + game->ray->planey
		* game->renderer->camerax;
	game->renderer->deltadistx = fabs(1 / game->renderer->raydirx);
	game->renderer->deltadisty = fabs(1 / game->renderer->raydiry);
	game->player->stepx = -1;
	game->player->stepy = -1;
	game->renderer->sidedistx = (game->player->pos->x - game->ray->mapx)
		* game->renderer->deltadistx;
	game->renderer->sidedisty = (game->player->pos->y
			- game->ray->mapy) * game->renderer->deltadisty;
	if (game->renderer->raydirx >= 0)
	{
		game->player->stepx = 1;
		game->renderer->sidedistx = (game->ray->mapx + 1.0
				- game->player->pos->x) * game->renderer->deltadistx;
	}
	if (game->renderer->raydiry >= 0)
	{
		game->player->stepy = 1;
		game->renderer->sidedisty = (game->ray->mapy + 1.0
				- game->player->pos->y) * game->renderer->deltadisty;
	}
}

void	launch_ray(t_game *game)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (game->renderer->sidedistx < game->renderer->sidedisty)
		{
			game->renderer->sidedistx += game->renderer->deltadistx;
			game->ray->mapx += game->player->stepx;
			game->renderer->side = 0;
		}
		else
		{
			game->renderer->sidedisty += game->renderer->deltadisty;
			game->ray->mapy += game->player->stepy;
			game->renderer->side = 1;
		}
		if (game->map->map[game->ray->mapy][game->ray->mapx] == '1'
			|| game->map->map[game->ray->mapy][game->ray->mapx] == 'm')
			hit = 1;
	}
}

void	get_dist(t_game *game)
{
	if (!game->renderer->side)
	{
		game->renderer->perpwalldist = (game->renderer->sidedistx
				- game->renderer->deltadistx);
		game->renderer->wallx = game->player->pos->y
			+ game->renderer->perpwalldist * game->renderer->raydiry;
		if (game->renderer->raydirx > 0)
			game->s = 4;
		else
			game->s = 2;
	}
	else
	{
		game->renderer->perpwalldist = (game->renderer->sidedisty
				- game->renderer->deltadisty);
		game->renderer->wallx = game->player->pos->x
			+ game->renderer->perpwalldist * game->renderer->raydirx;
		if (game->renderer->raydiry > 0)
			game->s = 1;
		else
			game->s = 3;
	}
}

void	get_wall_height(t_game *game)
{
	game->renderer->wallx -= floor(game->renderer->wallx);
	game->img[game->s]->pos.x = (int)(game->renderer->wallx * (double)128);
	if ((!game->renderer->side && game->renderer->raydirx < 0)
		|| (game->renderer->side == 1 && game->renderer->raydiry > 0))
		game->img[game->s]->pos.x = 128 - game->img[game->s]->pos.x - 1;
	game->renderer->lineheight = (int)(H / game->renderer->perpwalldist);
	game->renderer->drawstart = -game->renderer->lineheight / 2 + H / 2;
	if (game->renderer->drawstart < 0)
		game->renderer->drawstart = 0;
	game->renderer->drawend = game->renderer->lineheight / 2 + H / 2;
	if (game->renderer->drawend >= H)
		game->renderer->drawend = H;
}
