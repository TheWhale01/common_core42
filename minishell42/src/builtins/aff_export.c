/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrossett <jrossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 11:32:32 by teambersaw        #+#    #+#             */
/*   Updated: 2022/09/27 15:35:26 by jrossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_equal(char *str)
{
	if (!ft_strchr(str, '='))
	{
		ft_putstr(str);
		ft_putchar('\n');
		return (1);
	}
	return (0);
}

int	ft_len(t_list **list)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = *list;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

void	ft_put_export(char *str)
{
	int	i;

	i = 0;
	ft_putstr("declare -x ");
	if (ft_equal(str))
		return ;
	while (str[i] && (ft_isalpha(str[i]) || str[i] == '_'))
		ft_putchar(str[i++]);
	ft_putchar(str[i++]);
	ft_putchar('\"');
	while (str[i])
		ft_putchar(str[i++]);
	ft_putstr("\"\n");
}

void	ft_list_sort(t_list *list)
{
	t_list	*tmp;
	char	*str;
	char	*min;
	int		i;

	i = -1;
	min = "\0";
	str = "~";
	while (++i < ft_len(&list))
	{
		tmp = list;
		while (tmp)
		{
			if (tmp->content)
			{
				if (ft_strcmp(tmp->content, str) < 0
					&& ft_strcmp(tmp->content, min) > 0)
					str = tmp->content;
			}
			tmp = tmp->next;
		}
		min = str;
		ft_put_export(str);
		str = "~";
	}
}

void	ft_norme_exit(t_data *data)
{
	if (data->pipeline.nb_pipes == 0)
		ft_putstr_fd("exit\n", 1);
	ft_putstr_fd("exit: too many arguments\n", 2);
	g_global.rtn_val = 1;
}
