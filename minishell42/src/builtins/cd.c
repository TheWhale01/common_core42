/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 12:09:28 by jrossett          #+#    #+#             */
/*   Updated: 2022/10/05 13:41:49 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_norme(char *path, char *str)
{
	free(path);
	free(str);
}

void	ft_perror(char *join)
{
	ft_putstr_fd(join, 2);
	ft_putstr_fd(": ", 2);
	perror("\0");
	if (join && ft_strcmp(join, "echo: write error"))
		free(join);
}

int	ft_len_double(char **tab)
{
	int	i;

	i = 0;
	if (tab)
		while (tab[i])
			i++;
	return (i);
}

int	ft_path_cd(char **arg, char **path, t_data *data)
{
	char		*paths;

	g_global.rtn_val = 0;
	if (ft_len_double(arg) == 1)
	{
		paths = search_env("HOME", data);
		if (paths == NULL)
		{
			g_global.rtn_val = 1;
			return (ft_putstr_fd("cd: HOME not set\n", 2), 1);
		}
	}
	else if (ft_len_double(arg) == 2)
	{
		if (((char *)arg[1])[0] == '\0')
			return (1);
		paths = ft_strdup(arg[1]);
	}
	else
	{
		g_global.rtn_val = 1;
		return (ft_putstr_fd("cd: too many arugments\n", 2), 1);
	}
	*path = paths;
	return (0);
}

int	ft_cd(t_data *data, char **arg)
{
	char	*join;
	char	*str;
	char	*path;

	if (ft_verif_norme(arg, &path, data))
		return (1);
	str = ft_strjoin_free_s2("OLDPWD=", data->pwd);
	if (!chdir(path) || !arg[1])
	{
		if (!ft_lstexport(data, str))
			ft_lstadd_back(&data->envp, ft_lstnew(ft_strdup(str)));
		free(str);
		str = ft_strjoin_free_s2("PWD=", getcwd(NULL, 0));
		if (!ft_lstexport(data, str))
			ft_lstadd_back(&data->envp, ft_lstnew(ft_strdup(str)));
	}
	else
	{
		g_global.rtn_val = 1;
		join = ft_strjoin("cd: ", arg[1]);
		ft_perror(join);
	}
	ft_free_norme(path, str);
	update_pwd(data);
	return (0);
}
