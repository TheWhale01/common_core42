/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrossett <jrossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 01:36:06 by jrossett          #+#    #+#             */
/*   Updated: 2022/10/26 01:36:07 by jrossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_joinmap(int fd)
{
	char	*join;
	char	*line;

	join = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		join = ft_strjoin_free_s1(join, line);
		if (!join)
			return (free(line), NULL);
		free(line);
	}
	return (join);
}

int	ft_verif_join2(char *j, int i, t_map *map, t_player *player)
{
	while (j[++i])
	{
		if (j[i] != '\n' && j[i] != 'W' && j[i] != 'E' && j[i] != 'S'
			&& j[i] != 'N' && j[i] != '0' && j[i] != '1' && j[i] != ' ')
			return (free(j), 1);
		if (j[i] == 'S' || j[i] == 'N' || j[i] == 'E' || j[i] == 'W')
		{
			player->player = j[i];
			map->nb_player += 1;
		}
	}
	return (0);
}

char	*ft_verif_join(char *new_j, t_map *map, t_player *player)
{
	char	*j;
	int		i;

	i = 0;
	while (new_j[i] && new_j[i] == '\n')
		i++;
	if (new_j[i] == '\0')
		return (free(new_j), NULL);
	j = ft_strdup_2(new_j + i, '\0');
	if (!j)
		return (NULL);
	free(new_j);
	i = -1;
	if (ft_verif_join2(j, i, map, player))
		return (NULL);
	if (map->nb_player != 1)
		return (free(j), NULL);
	return (j);
}

int	ft_double_nl(char *join)
{
	int	i;
	int	v;

	i = -1;
	v = 0;
	while (join[++i])
	{
		if (join[i] == '\n')
			v += 1;
		else
			v = 0;
		if (v > 1)
			return (1);
	}
	return (0);
}

char	**ft_parse_map(int fd, t_map *map, t_player *player)
{
	char	**tab;
	char	*join;
	char	*new_join;

	join = ft_joinmap(fd);
	if (!join)
		return (NULL);
	new_join = ft_verif_join(join, map, player);
	if (!new_join)
		return (NULL);
	if (new_join[ft_strlen(new_join) - 1] == '\n' || ft_double_nl(new_join))
		return (free(new_join), NULL);
	tab = ft_split(new_join, '\n');
	free(new_join);
	return (tab);
}
