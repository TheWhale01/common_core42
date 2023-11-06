/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrossett <jrossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 01:35:29 by jrossett          #+#    #+#             */
/*   Updated: 2022/10/26 01:35:31 by jrossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*ft_free_elem(t_elem *elem)
{
	if (elem->so)
		free(elem->so);
	if (elem->no)
		free(elem->no);
	if (elem->we)
		free(elem->we);
	if (elem->ea)
		free(elem->ea);
	if (elem->f)
		ft_free_tab(elem->f);
	if (elem->c)
		ft_free_tab(elem->c);
	free(elem);
	elem = NULL;
	return (NULL);
}

void	ft_free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab && tab[++i])
		free(tab[i]);
	if (tab)
		free(tab);
	tab = NULL;
}

void	*ft_free_map(t_map *map)
{
	if (!map)
		return (NULL);
	if (map->elem)
		ft_free_elem(map->elem);
	if (map->map)
		ft_free_tab(map->map);
	free(map);
	map = NULL;
	return (NULL);
}

void	*ft_free_img(t_game *game, int var)
{
	int	i;

	i = -1;
	while (++i < var)
	{
		destroy_mlx(game->mlx, game->img[i]->img, 2);
		free(game->img[i]);
	}
	free(game->img);
	return (NULL);
}

void	*ft_free_game(t_game *game, int var)
{
	if (!game)
		return (NULL);
	if (game->map)
		ft_free_map(game->map);
	if (!game->img)
		return (free(game), NULL);
	if (game->img)
	{
		if (var < 0)
			ft_free_img(game, 5);
		else
			ft_free_img(game, var);
		if (var >= 0)
			return (free(game), NULL);
	}
	if (var == -2)
	{
		free(game->player);
		return (free(game), NULL);
	}
	ft_free_game_2(game);
	return (NULL);
}
