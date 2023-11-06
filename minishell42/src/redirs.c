/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:56:12 by hubretec          #+#    #+#             */
/*   Updated: 2022/10/03 16:24:56 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*skip_redirs(t_list	*tokens)
{
	t_token	*token;
	t_list	*tmp;

	tmp = tokens;
	token = (t_token *)tmp->content;
	while (tmp && (token->token == REDIR_IN || token->token == REDIR_OUT
			|| token->token == D_REDIR_IN || token->token == D_REDIR_OUT))
	{
		tmp = tmp->next->next;
		if (tmp)
			token = (t_token *)tmp->content;
	}
	return (tmp);
}

void	redir_in(t_data *data, t_list *file, int mode)
{
	int		file_fd;

	if (data->fd_in != STDIN_FILENO)
	{
		dup2(data->fd_in, STDIN_FILENO);
		close(data->fd_in);
	}
	data->fd_in = dup(STDIN_FILENO);
	if (mode == D_REDIR_IN && !g_global.sigint)
	{
		g_global.eof = ft_strdup(((t_token *)file->content)->str);
		heredoc(data);
	}
	else if (mode == REDIR_IN)
	{
		file_fd = open(((t_token *)file->content)->str, O_RDONLY, 0644);
		if (file_fd == -1 && !g_global.fd_err)
			g_global.fd_err = file_error(((t_token *)file->content)->str);
		else if (file_fd != -1)
		{
			dup2(file_fd, STDIN_FILENO);
			close(file_fd);
		}
	}
}

void	redir_out(t_data *data, t_list *file, int mode)
{
	int		file_fd;
	char	*filename;

	if (data->fd_out != STDOUT_FILENO)
	{
		dup2(data->fd_out, STDOUT_FILENO);
		close(data->fd_out);
	}
	file_fd = -1;
	filename = ((t_token *)file->content)->str;
	data->fd_out = dup(STDOUT_FILENO);
	if (mode == D_REDIR_OUT && !g_global.fd_err)
		file_fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (mode == REDIR_OUT && !g_global.fd_err)
		file_fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (file_fd == -1 && !g_global.fd_err)
		g_global.fd_err = file_error(filename);
	else if (file_fd != -1)
	{
		dup2(file_fd, STDOUT_FILENO);
		close(file_fd);
	}
}

void	make_redirs(t_data *data, t_list *start)
{
	t_list	*tmp;
	t_token	*token;

	tmp = start;
	while (tmp && ((t_token *)tmp->content)->token != PIPE)
	{
		token = (t_token *)tmp->content;
		if (token->token == REDIR_OUT || token->token == D_REDIR_OUT)
			redir_out(data, tmp->next, token->token);
		else if (token->token == REDIR_IN || token->token == D_REDIR_IN)
			redir_in(data, tmp->next, token->token);
		tmp = tmp->next;
	}
	if (g_global.fd_err)
	{
		if (*g_global.fd_err)
			ft_putendl_fd(g_global.fd_err, STDERR_FILENO);
		restore_redirs(data);
	}
}

void	restore_redirs(t_data *data)
{
	g_global.heredoc_pid = -1;
	if (data->fd_in != STDIN_FILENO)
	{
		dup2(data->fd_in, STDIN_FILENO);
		close(data->fd_in);
		data->fd_in = STDIN_FILENO;
	}
	if (data->fd_out != STDOUT_FILENO)
	{
		dup2(data->fd_out, STDOUT_FILENO);
		close(data->fd_out);
		data->fd_out = STDOUT_FILENO;
	}
}
