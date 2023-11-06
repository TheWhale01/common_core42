/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 16:55:11 by teambersaw        #+#    #+#             */
/*   Updated: 2022/10/05 13:40:20 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_verif_norme(char **arg, char **path, t_data *data)
{
	char	*join;
	DIR		*dir;

	if (ft_path_cd(arg, path, data))
		return (1);
	dir = opendir(*path);
	if (!dir)
	{
		g_global.rtn_val = 1;
		join = ft_strjoin_free_s2("cd: ", *path);
		return (ft_perror(join), 1);
	}
	closedir(dir);
	return (0);
}

int	ft_option(char *str)
{
	int	i;

	i = 0;
	if (str[0] != '-')
		return (0);
	while (str[++i])
		if (str[i] != 'n')
			return (0);
	return (1);
}

int	ft_echo_2(char **arg, int i, int var)
{
	while (arg[i])
	{
		if (ft_putstr(arg[i++]) == -1)
		{
			g_global.rtn_val = 1;
			return (ft_perror("echo: write error"), 1);
		}
		if (arg[i] && ((char *)arg[i])[0] != '\0')
		{
			if (ft_putstr(" ") == -1)
			{
				g_global.rtn_val = 1;
				return (ft_perror("echo: write error"), 1);
			}
		}
	}
	if (var == 0)
	{
		if (ft_putstr("\n") == -1)
		{
			g_global.rtn_val = 1;
			return (ft_perror("echo: write error"), 1);
		}
	}
	return (0);
}

int	ft_echo(char **arg)
{
	int		i;
	int		var;

	g_global.rtn_val = 0;
	var = 0;
	if (ft_len_double(arg) == 1)
	{
		if (ft_putstr("\n") == -1)
		{
			g_global.rtn_val = 1;
			return (ft_perror("echo: write error"), 1);
		}
		return (0);
	}
	i = 1;
	while (arg[i] && ft_option(arg[i]))
	{
		var = 1;
		i++;
	}
	return (ft_echo_2(arg, i, var));
}
