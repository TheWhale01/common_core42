/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 14:48:28 by hubretec          #+#    #+#             */
/*   Updated: 2022/03/08 18:47:53 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "mlx.h"
#include "libft.h"
#include "so_long.h"

void	safe_destroy(char *str, void *mlx, void *ptr)
{
	if (!ft_strcmp(str, "window") && mlx && ptr)
		mlx_destroy_window(mlx, ptr);
	else if (!ft_strcmp(str, "display") && mlx)
		mlx_destroy_display(mlx);
	else if (!ft_strcmp(str, "image") && mlx && ptr)
		mlx_destroy_image(mlx, ptr);
}

void	free_img(t_game *game)
{
	safe_destroy("image", game->mlx, game->player.back.img);
	safe_destroy("image", game->mlx, game->player.left.img);
	safe_destroy("image", game->mlx, game->player.right.img);
	safe_destroy("image", game->mlx, game->player.front.img);
	safe_destroy("image", game->mlx, game->player.exit_back.img);
	safe_destroy("image", game->mlx, game->player.exit_left.img);
	safe_destroy("image", game->mlx, game->player.exit_right.img);
	safe_destroy("image", game->mlx, game->player.exit_front.img);
	safe_destroy("image", game->mlx, game->map.assets.collectible.img);
	safe_destroy("image", game->mlx, game->map.assets.empty.img);
	safe_destroy("image", game->mlx, game->map.assets.exit.img);
	safe_destroy("image", game->mlx, game->map.assets.wall.img);
}

void	free_game(t_game *game)
{
	free_tab(game->map.map);
	free_img(game);
	safe_destroy("window", game->mlx, game->mlx_win);
	safe_destroy("display", game->mlx, NULL);
	free(game->mlx);
}
