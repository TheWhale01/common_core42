/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrossett <jrossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 01:35:46 by jrossett          #+#    #+#             */
/*   Updated: 2022/10/26 01:35:47 by jrossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_renderer(t_game *game)
{
	game->renderer = malloc(sizeof(t_renderer) * 1);
	if (!game->renderer)
		exit_game(game, ERR_MALLOC, -1);
}
