/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 04:58:04 by jrossett          #+#    #+#             */
/*   Updated: 2022/09/16 10:23:49 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_put_verif(char *arg)
{
	g_global.rtn_val = 2;
	ft_putstr_fd("unset: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

int	ft_verif_unset(char	*str)
{
	int	i;

	i = 0;
	if (str[i] && ft_isdigit(str[i]))
		return (1);
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	if (str[i] == '\0')
		return (0);
	return (0);
}

int	ft_lstunset(t_list **lst, char *str)
{
	t_list	*del;
	t_list	*tmp;
	size_t	size;

	tmp = *lst;
	size = ft_strlen(str);
	while (tmp)
	{
		if (ft_strncmp((char *)tmp->content, str, size) == 0)
		{
			del = ft_lstpop(lst, tmp);
			ft_lstdelone(del, free);
			return (0);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	ft_unset(t_data *data, char **arg)
{
	int	i;

	g_global.rtn_val = 0;
	if (ft_len_double(arg) == 1)
		return (0);
	i = 0;
	while (arg[++i])
	{
		if (ft_verif_unset(arg[i]))
			ft_put_verif(arg[i]);
		else
		{
			if (!strncmp(arg[i], "PATH", 4) && ft_strlclen(arg[i], "=") == 4)
			{
				if (data->path)
					free_tab(data->path);
				data->path = NULL;
			}
			ft_lstunset(&data->envp, arg[i]);
		}
	}
	return (0);
}
