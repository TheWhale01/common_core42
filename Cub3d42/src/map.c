/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrossett <jrossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 01:36:49 by jrossett          #+#    #+#             */
/*   Updated: 2022/10/26 01:36:49 by jrossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_print_img(int camera, t_game *game)
{
	int	i;
	int	color;

	i = -1;
	game->img[game->s]->step = 1.0 * 128 / game->renderer->lineheight;
	game->img[game->s]->tex_pos = (game->renderer->drawstart - H / 2
			+ game->renderer->lineheight / 2) * game->img[game->s]->step;
	while (++i < H)
	{
		if (i < game->renderer->drawstart && i < game->renderer->drawend)
			color = game->map->elem->ccolor;
		else if (i > game->renderer->drawstart && i > game->renderer->drawend)
			color = game->map->elem->fcolor;
		else
		{
			game->img[game->s]->pos.y = (int)game->img[game->s]->tex_pos & 127;
			game->img[game->s]->tex_pos += game->img[game->s]->step;
			color = *(unsigned int *)(game->img[game->s]->addr
					+ ((int)game->img[game->s]->pos.y * game->img[game->s]->len
						+ (int)game->img[game->s]->pos.x
						* (game->img[game->s]->bpp / 8)));
		}
		mlx_put_pixel(game, camera, i, color);
	}
}

void	init_ray2(t_ray *ray, t_game *game)
{
	if (game->player->player == 'S')
	{
		ray->dirx = 0.0;
		ray->diry = 1.0;
		ray->planex = -0.72;
		ray->planey = 0.0;
	}
	if (game->player->player == 'W')
	{
		ray->dirx = -1;
		ray->diry = 0.0;
		ray->planex = 0.0;
		ray->planey = -0.72;
	}
}

t_ray	*init_ray(t_game *game)
{
	t_ray	*ray;

	ray = malloc(sizeof(t_ray) * 1);
	if (!ray)
		return (NULL);
	ray->dirx = 0.0;
	ray->diry = -1.0;
	ray->planex = 0.72;
	ray->planey = 0.0;
	if (game->player->player == 'E')
	{
		ray->dirx = 1.0;
		ray->diry = 0.0;
		ray->planex = 0.0;
		ray->planey = 0.72;
	}
	init_ray2(ray, game);
	return (ray);
}

void	cub3d(t_game *game)
{
	int		i;

	i = -1;
	while (++i < L)
	{
		game->ray->mapx = (int)game->player->pos->x;
		game->ray->mapy = (int)game->player->pos->y;
		set_renderer(i, game);
		launch_ray(game);
		get_dist(game);
		get_wall_height(game);
		ft_print_img(i, game);
	}
}

void	init_window(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		exit_game(game, ERR_MLX, -1);
	ft_create_img(game);
	game->mlx_win = mlx_new_window(game->mlx, L, H, "cub3D");
	if (!game->mlx_win)
		exit_game(game, ERR_WIN, -1);
	game->ray = init_ray(game);
	if (!game->ray)
		exit_game(game, ERR_MALLOC, -1);
	init_renderer(game);
	game->backward = 0;
	game->forward = 0;
	game->left = 0;
	game->right = 0;
	game->t_right = 0;
	game->t_left = 0;
}
