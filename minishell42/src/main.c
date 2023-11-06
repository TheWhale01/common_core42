/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 21:33:00 by hubretec          #+#    #+#             */
/*   Updated: 2022/10/05 09:05:18 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	g_global;

void	init_global(t_global *global, t_data *data)
{
	global->fd[0] = -1;
	global->fd[1] = -1;
	global->eof = NULL;
	global->rtn_val = 0;
	global->sigint = 0;
	global->heredoc_pid = -1;
	global->line = &(data->line);
}

void	init(t_data *data, int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	errno = 0;
	data->fd_in = STDIN_FILENO;
	data->fd_out = STDOUT_FILENO;
	g_global.fd_err = NULL;
	data->line = NULL;
	data->envp = create_list(envp);
	data->path = get_path_env(search_env("PATH", data));
	data->tokens = NULL;
	data->pwd = getcwd(NULL, 0);
	data->pipeline.nb_pipes = 0;
	init_global(&g_global, data);
	init_signals();
}

int	main(int ac, char **av, char **envp)
{
	t_list	*lst;
	t_data	data;

	init(&data, ac, av, envp);
	while (1)
	{
		data.line = ft_prompt(&data);
		lst = format(data.line);
		tokenize(&data, lst);
		if (check_syntax(&data))
		{
			expander(&data);
			if (data.tokens && !search_token(data.tokens, PIPE, 0))
				exec(&data);
			else if (data.tokens)
				pipeline(&data);
			free(g_global.fd_err);
			g_global.fd_err = NULL;
		}
		free_tokens(data.tokens);
		data.tokens = NULL;
		data.line = NULL;
		g_global.sigint = 0;
	}
	return (0);
}
