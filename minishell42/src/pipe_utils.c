/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 20:25:12 by hubretec          #+#    #+#             */
/*   Updated: 2022/10/05 14:09:48 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_nb_tokens(t_list *tokens, int e_token)
{
	int		nb;
	t_list	*tmp;
	t_token	*token;

	nb = 0;
	tmp = tokens;
	while (tmp)
	{
		token = (t_token *)tmp->content;
		if (token->token == e_token)
			nb++;
		tmp = tmp->next;
	}
	return (nb);
}

t_list	*skip_pipes(t_list *tokens, int pos)
{
	t_list	*tmp;

	tmp = tokens;
	if (!pos)
		return (tmp);
	while (tmp && pos)
	{
		if (((t_token *)tmp->content)->token == PIPE)
			pos--;
		tmp = tmp->next;
	}
	return (tmp);
}

void	close_pipes(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->pipeline.nb_pipes)
	{
		if (data->pipeline.pipes && data->pipeline.pipes[i]
			&& data->pipeline.pipes[i][0] != -1
			&& data->pipeline.pipes[i][1] != -1)
		{
			close(data->pipeline.pipes[i][0]);
			close(data->pipeline.pipes[i][1]);
		}
		if (data->pipeline.pipes && data->pipeline.pipes[i])
		{
			data->pipeline.pipes[i][0] = -1;
			data->pipeline.pipes[i][1] = -1;
		}
	}
}

void	free_pipeline(t_data *data)
{
	int	i;

	i = -1;
	if (!data->pipeline.nb_pipes)
		return ;
	close_pipes(data);
	while (++i < data->pipeline.nb_pipes)
		free(data->pipeline.pipes[i]);
	free(data->pipeline.pipes);
	free(data->pipeline.children);
	restore_redirs(data);
}

void	safe_exit(t_data *data, char *str)
{
	free_pipeline(data);
	exit_cmd(EXIT_FAILURE, data, str, NULL);
	exit(EXIT_FAILURE);
}
