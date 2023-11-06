/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 14:01:08 by hubretec          #+#    #+#             */
/*   Updated: 2022/02/17 10:12:27 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "push_swap.h"

int	tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		i++;
	return (i);
}

void	exit_with_msg(char *str, char **tab)
{
	free_tab(tab);
	if (str)
		ft_putendl_fd(str, STDERR);
	exit(0);
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

void	*free_lst(t_list **lst)
{
	ft_lstclear(lst, free);
	return (NULL);
}
