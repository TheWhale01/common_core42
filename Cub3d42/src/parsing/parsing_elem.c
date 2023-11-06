/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_elem.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrossett <jrossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 01:36:00 by jrossett          #+#    #+#             */
/*   Updated: 2022/10/26 01:36:01 by jrossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_stor(char *line, char *str)
{
	int	i;
	int	j;

	i = 0;
	if (!line || line[i] != ' ')
		return (NULL);
	while (line && line[i] == ' ')
		i++;
	if (!line || line[i] == '\0' || line[i] == '\n')
		return (NULL);
	j = i;
	while (line && line[i] && line[i] != '\n')
		i++;
	if (!line || !line[i])
		return (NULL);
	if (str)
		free(str);
	str = ft_strdup_2(line + j, '\n');
	return (str);
}

char	**ft_stor_tab(char *line, char **tab)
{
	char	*s;
	int		i;

	i = 0;
	if (!line || line[i] != ' ')
		return (NULL);
	tab = ft_split(line, ',');
	if (!tab)
		return (NULL);
	if (tablen(tab) != 3)
		return (ft_free_tab(tab), NULL);
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\0')
		return (ft_free_tab(tab), NULL);
	s = ft_strdup_2(tab[2], '\n');
	free(tab[2]);
	tab[2] = s;
	return (tab);
}

int	ft_elem_cmp(char *line, t_elem *elem)
{
	if (!ft_strncmp(line, "NO", 2))
		elem->no = ft_stor(line + 2, elem->no);
	else if (!ft_strncmp(line, "EA", 2))
		elem->ea = ft_stor(line + 2, elem->ea);
	else if (!ft_strncmp(line, "SO", 2))
		elem->so = ft_stor(line + 2, elem->so);
	else if (!ft_strncmp(line, "WE", 2))
		elem->we = ft_stor(line + 2, elem->we);
	else if (!ft_strncmp(line, "F", 1))
	{
		if (elem->f)
			ft_free_tab(elem->f);
		elem->f = ft_stor_tab(line + 1, elem->f);
	}
	else if (!ft_strncmp(line, "C", 1))
	{
		if (elem->c)
			ft_free_tab(elem->c);
		elem->c = ft_stor_tab(line + 1, elem->c);
	}
	else
		return (1);
	elem->nb_elem += 1;
	return (0);
}

int	ft_parse_line(char *line, t_elem *elem)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] == '\0')
		return (1);
	if (line[i] == '\n')
		return (1);
	if (ft_elem_cmp(&line[i], elem))
		return (1);
	return (0);
}

int	ft_parse_elem(int fd, t_elem *elem)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (1);
	while (line != NULL)
	{
		if (line[0] == '\n')
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (ft_parse_line(line, elem))
			return (free(line), 1);
		free(line);
		if (elem->nb_elem >= 6)
			break ;
		line = get_next_line(fd);
	}
	return (0);
}
