/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 07:40:34 by jrossett          #+#    #+#             */
/*   Updated: 2022/10/05 13:42:24 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_data *data)
{
	char	*pwd;

	g_global.rtn_val = 0;
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		printf("%s\n", data->pwd);
		return (1);
	}
	free(data->pwd);
	data->pwd = pwd;
	printf("%s\n", data->pwd);
	return (0);
}

void	update_pwd(t_data *data)
{
	data->pwd = getcwd(NULL, 0);
	if (!data->pwd)
	{
		ft_putendl_fd("cd: error retrieving current directory: getcwd: \
cannot access parent directories: \
No such file or directory", STDERR_FILENO);
		data->pwd = ft_strjoin_free_s1(search_env("OLDPWD", data), "/../");
		ft_lstadd_back(&data->envp, ft_lstnew(ft_strdup(data->pwd)));
	}
}
