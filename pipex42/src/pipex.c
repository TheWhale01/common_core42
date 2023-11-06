/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:26:09 by hubretec          #+#    #+#             */
/*   Updated: 2022/03/24 14:26:45 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "pipex.h"

char	**get_path_env(char **env)
{
	while (*env)
	{
		if (!ft_strncmp(*env, "PATH", 4))
			return (ft_split(&((*env)[5]), ':'));
		env++;
	}
	return (NULL);
}

char	*get_path_cmd(char *cmd, char **env)
{
	char	*tmp;
	char	*path_cmd;

	if (!access(cmd, F_OK))
		return (cmd);
	while (env && *env)
	{
		tmp = ft_strdup(*env);
		path_cmd = ft_strjoin(tmp, "/");
		path_cmd = ft_strjoin(path_cmd, cmd);
		if (!access(path_cmd, F_OK))
			return (path_cmd);
		free(path_cmd);
		env++;
	}
	return (NULL);
}

int	exec_cmd(char *cmd, char **env)
{
	int		result;
	char	*path_cmd;
	char	**tmp;
	char	**path;

	result = 1;
	path = get_path_env(env);
	tmp = ft_split(cmd, ' ');
	path_cmd = get_path_cmd(tmp[0], path);
	if (!path_cmd)
	{
		result = 0;
		perror(tmp[0]);
	}
	else if (execve(path_cmd, tmp, path) == -1)
	{
		result = 0;
		perror(tmp[0]);
	}
	free_tab(tmp);
	free_tab(path);
	free(path_cmd);
	return (result);
}
