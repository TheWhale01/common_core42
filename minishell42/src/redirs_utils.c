/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 13:49:30 by hubretec          #+#    #+#             */
/*   Updated: 2022/10/03 16:22:39 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*file_error(char *filename)
{
	char	*error;

	error = ft_strjoin(filename, ": ");
	error = ft_strjoin_free_s1(error, strerror(errno));
	return (error);
}

void	heredoc_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		free(g_global.eof);
		if (g_global.fd[1] != -1)
			close(g_global.fd[1]);
		g_global.sigint = 1;
		exit(130);
	}
}

void	heredoc_child(t_data *data)
{
	char	*line;

	signal(SIGINT, heredoc_handler);
	close(g_global.fd[0]);
	free_pipeline(data);
	exit_cmd(EXIT_SUCCESS, data, NULL, NULL);
	while (1)
	{
		line = readline("> ");
		if (!line || (ft_strlen(line) == ft_strlen(g_global.eof)
				&& !ft_strcmp(line, g_global.eof)))
		{
			if (!line)
				printf("Warning: end-of-file sent. Expected `%s'\n",
					g_global.eof);
			free(line);
			free(g_global.eof);
			g_global.eof = NULL;
			close(g_global.fd[1]);
			exit(EXIT_SUCCESS);
		}
		line = ft_strjoin_free_s1(line, "\n");
		write(g_global.fd[1], line, ft_strlen(line));
		free(line);
	}
}

void	heredoc(t_data *data)
{
	pipe(g_global.fd);
	g_global.heredoc_pid = fork();
	if (!g_global.heredoc_pid)
		heredoc_child(data);
	else
	{
		close(g_global.fd[1]);
		dup2(g_global.fd[0], STDIN_FILENO);
		close(g_global.fd[0]);
	}
	wait_set_rtn_value(g_global.heredoc_pid);
	if (g_global.rtn_val == 130)
		g_global.fd_err = ft_strdup("");
	free(g_global.eof);
	g_global.eof = NULL;
	g_global.heredoc_pid = -1;
}
