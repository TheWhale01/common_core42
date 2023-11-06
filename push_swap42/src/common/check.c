/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 11:49:56 by hubretec          #+#    #+#             */
/*   Updated: 2022/02/17 10:19:06 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "push_swap.h"

char	**ft_tabadd(char **tab, char **add)
{
	int		i;
	int		j;
	char	**result;

	result = malloc(sizeof(char *) * (tablen(add) + tablen(tab) + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (tab && tab[i])
	{
		result[i] = ft_strdup(tab[i]);
		if (!result[i++])
			return (free_tab(result));
	}
	j = -1;
	while (add[++j])
	{
		result[i] = ft_strdup(add[j]);
		if (!result[i++])
			return (free_tab(result));
	}
	free_tab(tab);
	free_tab(add);
	result[i] = NULL;
	return (result);
}

char	**get_tab(int ac, char **av)
{
	int		i;
	char	**tab;
	char	**tmp;

	i = 0;
	tab = NULL;
	while (++i < ac)
	{
		tmp = ft_split(av[i], ' ');
		if (!tmp)
			exit_with_msg("Memory Error.", tab);
		tab = ft_tabadd(tab, tmp);
	}
	return (tab);
}

int	check_double(char **tab)
{
	int	i;
	int	j;
	int	index1;
	int	index2;

	i = -1;
	while (tab[++i])
	{
		j = i + 1;
		index1 = 0;
		index2 = 0;
		if ((ft_strlen(tab[i]) > 2 && (tab[i][0] == '+' || tab[i][0] == '-')
			&& tab[i][1] == '0') || (ft_strlen(tab[i]) > 1 && tab[i][0] == '0'))
			return (1);
		while (tab[j])
		{
			if (tab[i][0] == '+')
				index1 = 1;
			if (tab[j][0] == '+')
				index2 = 1;
			if (!ft_strcmp(&tab[i][index1], &tab[j++][index2]))
				return (1);
		}
	}
	return (0);
}

char	**check(int ac, char **av)
{
	int		i;
	int		j;
	char	**tab;

	if (ac == 1)
		exit(0);
	i = -1;
	tab = get_tab(ac, av);
	while (tab[++i])
	{
		j = 0;
		if (!ft_isdigit(tab[i][j]) && tab[i][j] != '-' && tab[i][j] != '+')
			exit_with_msg("Error", tab);
		else if (ft_strlen(tab[i]) == 1
			&& (tab[i][j] == '+' || tab[i][j] == '-'))
			exit_with_msg("Error", tab);
		while (tab[i][++j])
			if (!ft_isdigit(tab[i][j]))
				exit_with_msg("Error", tab);
	}
	if (tablen(tab) == 1)
		return (free_tab(tab));
	if (check_double(tab))
		exit_with_msg("Error", tab);
	return (tab);
}
