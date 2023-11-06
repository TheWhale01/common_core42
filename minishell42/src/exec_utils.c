/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 09:54:50 by hubretec          #+#    #+#             */
/*   Updated: 2022/10/05 09:02:37 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_dir(char *filename)
{
	struct stat	path;

	if (!filename)
		return (0);
	stat(filename, &path);
	return (S_ISDIR(path.st_mode));
}

void	exec_errors(char *path, char *args, char **msg, int *code)
{
	*code = 0;
	*msg = NULL;
	if (!path && args && *args != '/' && ft_strncmp(args, "./", 2))
	{
		*code = 127;
		*msg = ": command not found.";
	}
	else if (!path)
	{
		*code = 127;
		*msg = ": No such file or directory.";
	}
	else if (*args && is_dir(path))
	{
		*code = 126;
		*msg = ": is a directory.";
	}
}

int	get_nb_args(t_list *tokens)
{
	int		nb_tokens;
	t_list	*tmp;
	t_token	*token;

	if (!tokens)
		return (0);
	nb_tokens = 0;
	tmp = tokens;
	while (tmp && ((t_token *)tmp->content)->token != PIPE)
	{
		token = (t_token *)tmp->content;
		if (token->token == CMD || token->token == WORD)
			nb_tokens++;
		else if (token->token == REDIR_IN || token->token == D_REDIR_IN
			|| token->token == REDIR_OUT || token->token == D_REDIR_OUT)
			tmp = tmp->next;
		tmp = tmp->next;
	}
	return (nb_tokens);
}

char	**get_args(t_list *tokens)
{
	int		i;
	char	**args;
	t_list	*tmp;
	t_token	*token;

	if (!tokens)
		return (NULL);
	args = malloc(sizeof(char *) * (get_nb_args(tokens) + 1));
	if (!args)
		return (NULL);
	i = 0;
	tmp = tokens;
	while (tmp && ((t_token *)tmp->content)->token != PIPE)
	{
		token = (t_token *)tmp->content;
		if (token->token == REDIR_IN || token->token == D_REDIR_IN
			|| token->token == REDIR_OUT || token->token == D_REDIR_OUT)
			tmp = tmp->next;
		else if (token->token == CMD || token->token == WORD)
			args[i++] = token->str;
		tmp = tmp->next;
	}
	args[i] = NULL;
	return (args);
}
