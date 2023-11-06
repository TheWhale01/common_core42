/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrossett <jrossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 15:54:40 by hubretec          #+#    #+#             */
/*   Updated: 2022/09/28 12:40:55 by jrossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_home(t_data *data)
{
	int		len;
	char	*home;
	char	*start;

	start = search_env("HOME", data);
	home = ft_rstrstr(data->pwd, start);
	if (!home)
		home = data->pwd;
	else if (start)
	{
		len = ft_strlen(start);
		if (len)
		{
			if (start[len - 1] == '/')
				home = ft_strjoin("~/", home);
			else
				home = ft_strjoin("~", home);
		}
	}
	free(start);
	return (home);
}

void	free_d(t_data *data)
{
	ft_lstclear(&data->envp, free);
	free_tab(data->path);
	free(data->pwd);
}

char	*get_prompt(t_data *data)
{
	char	*dir;
	char	*user;
	char	*prompt;

	dir = get_home(data);
	user = search_env("USER", data);
	if (!user)
		user = ft_strdup("user");
	prompt = ft_strjoin_free_s1(user, "@minishell:");
	if (!ft_strchr(dir, '~'))
		prompt = ft_strjoin_free_s1(prompt, dir);
	else
		prompt = ft_strjoin_free_s1_s2(prompt, dir);
	prompt = ft_strjoin_free_s1(prompt, "$ ");
	return (prompt);
}

char	*ft_prompt(t_data *data)
{
	char	*line;
	char	*prompt;

	prompt = get_prompt(data);
	line = readline(prompt);
	if (line && *line)
		add_history(line);
	while (!check_quotes(line))
	{
		free(prompt);
		ft_putendl_fd("minishell: syntax error.", STDERR_FILENO);
		prompt = get_prompt(data);
		line = readline(prompt);
	}
	free(prompt);
	if (!line)
	{
		free_d(data);
		printf("exit\n");
		exit(0);
	}
	return (line);
}
