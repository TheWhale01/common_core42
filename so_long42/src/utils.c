/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 16:52:27 by hubretec          #+#    #+#             */
/*   Updated: 2022/03/23 13:38:43 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "mlx.h"
#include "libft.h"
#include "so_long.h"

char	**add_line(char **tab, char *line)
{
	int		i;
	int		len;
	char	**new;

	new = malloc(sizeof(char *) * (tablen(tab) + 2));
	if (!new)
		return (NULL);
	i = 0;
	len = ft_strlen(line);
	if (line[len - 1] == '\n')
		line[len - 1] = '\0';
	while (tab && tab[i])
	{
		new[i] = ft_strdup(tab[i]);
		free(tab[i++]);
	}
	new[i++] = line;
	new[i] = NULL;
	free(tab);
	return (new);
}

void	exit_msg(int exit_code, char *str, t_game *game)
{
	if (str)
	{
		if (exit_code == EXIT_FAILURE)
			ft_putendl_fd("Error", STDERR);
		ft_putendl_fd(str, STDERR);
	}
	free_game(game);
	exit(exit_code);
}

void	*free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab && tab[++i])
		free(tab[i]);
	free(tab);
	return (NULL);
}

int	is_in(char **tab, char c)
{
	int	i;
	int	j;
	int	count;

	i = -1;
	count = 0;
	while (tab && tab[++i])
	{
		j = -1;
		while (tab[i][++j])
			if (tab[i][j] == c)
				count++;
	}
	return (count);
}

int	tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		i++;
	return (i);
}
