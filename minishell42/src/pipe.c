/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:09:59 by hubretec          #+#    #+#             */
/*   Updated: 2022/10/05 14:13:42 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	connect_pipes(t_data *data, t_list *start, int child_index)
{
	if (child_index != data->pipeline.nb_pipes
		&& !search_token(start, REDIR_OUT, 1)
		&& !search_token(start, D_REDIR_OUT, 1))
	{
		close(data->pipeline.pipes[child_index][0]);
		dup2(data->pipeline.pipes[child_index][1], STDOUT_FILENO);
		close(data->pipeline.pipes[child_index][1]);
	}
	if (child_index
		&& !search_token(start, REDIR_IN, 1)
		&& !search_token(start, D_REDIR_IN, 1))
	{
		close(data->pipeline.pipes[child_index - 1][1]);
		dup2(data->pipeline.pipes[child_index - 1][0], STDIN_FILENO);
		close(data->pipeline.pipes[child_index - 1][0]);
	}
}

void	init_pipeline(t_data *data, t_pipeline *pipeline)
{
	int	i;

	i = -1;
	data->pipeline.nb_pipes = get_nb_tokens(data->tokens, PIPE);
	data->pipeline.nb_children = data->pipeline.nb_pipes + 1;
	data->pipeline.children = malloc(sizeof(pid_t)
			* data->pipeline.nb_children);
	pipeline->pipes = malloc(sizeof(int *) * pipeline->nb_pipes);
	if (!data->pipeline.children || !data->pipeline.pipes)
		safe_exit(data, "Memory allocation error");
	while (++i < pipeline->nb_pipes)
	{
		pipeline->pipes[i] = ft_calloc(sizeof(int), 2);
		if (!pipeline->pipes[i])
			safe_exit(data, "Memory allocation error");
	}
	i = -1;
	while (++i < pipeline->nb_pipes)
		if (pipe(data->pipeline.pipes[i]) == -1)
			safe_exit(data, "Could not create pipe");
}

void	exec_pipe(t_data *data, int child_index)
{
	char	**args;
	t_list	*start;

	start = skip_pipes(data->tokens, child_index);
	args = get_args(skip_redirs(start));
	if (!args || !*args)
	{
		free_pipeline(data);
		exit_cmd(EXIT_SUCCESS, data, NULL, args);
		exit(EXIT_SUCCESS);
	}
	connect_pipes(data, start, child_index);
	close_pipes(data);
	if (!g_global.fd_err && is_builtin(*args))
	{
		if (!ft_strcmp(*args, "exit"))
			free_pipeline(data);
		exec_builtin(args, data);
	}
	else if (!g_global.fd_err)
		exec_cmd(args, data);
	if (ft_strcmp(*args, "exit"))
		free_pipeline(data);
	exit_cmd(EXIT_SUCCESS, data, NULL, args);
	exit(EXIT_SUCCESS);
}

void	pipeline(t_data *data)
{
	int	i;

	i = -1;
	init_pipeline(data, &data->pipeline);
	while (++i < data->pipeline.nb_children)
	{
		make_redirs(data, skip_pipes(data->tokens, i));
		data->pipeline.children[i] = fork();
		if (data->pipeline.children[i] == -1)
			safe_exit(data, "Could not create fork");
		if (!data->pipeline.children[i])
			exec_pipe(data, i);
		else
			restore_redirs(data);
	}
	i = -1;
	close_pipes(data);
	while (++i < data->pipeline.nb_children)
		wait_set_rtn_value(data->pipeline.children[i]);
	free_pipeline(data);
	data->pipeline.nb_pipes = 0;
	data->pipeline.nb_children = 0;
	if (g_global.rtn_val == 139)
		ft_putendl_fd("Segmentation fault (core dumped).", STDERR_FILENO);
}
