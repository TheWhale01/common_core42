/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrossett <jrossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 01:36:42 by jrossett          #+#    #+#             */
/*   Updated: 2022/10/26 01:36:42 by jrossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_game_2(t_game *game)
{
	free(game->renderer);
	game->renderer = NULL;
	free(game->player->pos);
	game->player->pos = NULL;
	free(game->player);
	game->player = NULL;
	destroy_mlx(game->mlx, game->mlx_win, 0);
	destroy_mlx(game->mlx, NULL, 1);
	free(game->mlx);
	free(game->ray);
	game->ray = NULL;
	game->mlx = NULL;
	free(game);
	game = NULL;
}

int	ft_game(t_game *game)
{
	if (game->forward == 1)
		move_forward(game);
	if (game->backward == 1)
		move_backward(game);
	if (game->left == 1 || game->right == 1)
		move_sideward(game);
	if (game->t_left == 1)
		turn_left(game);
	if (game->t_right == 1)
		turn_right(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img[0]->img, 0, 0);
	return (0);
}

int	main(int ac, char **av)
{
	t_game	*game;

	game = ft_parsing(ac, av);
	init_window(game);
	cub3d(game);
	mlx_hook(game->mlx_win, 2, (1 << 0), do_event, game);
	mlx_hook(game->mlx_win, 3, (1 << 1), stop_event, game);
	mlx_hook(game->mlx_win, 17, (1 << 0), exit_game_v, game);
	mlx_loop_hook(game->mlx, ft_game, game);
	mlx_loop(game->mlx);
	return (0);
}
