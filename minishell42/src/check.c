/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 13:42:13 by hubretec          #+#    #+#             */
/*   Updated: 2022/10/05 09:43:59 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir(char *str)
{
	return (!ft_strncmp(str, ">>", 2) || !ft_strncmp(str, "<<", 2)
		|| *str == '>' || *str == '<');
}

int	check_order(t_list *tokens)
{
	t_token	*token;

	token = (t_token *)tokens->content;
	return ((token->token == PIPE && (!tokens->next
				|| ((t_token *)tokens->next->content)->token == PIPE))
		|| (is_redir(token->str) && (!tokens->next
				|| (is_redir(((t_token *)tokens->next->content)->str)
					|| ((t_token *)tokens->next->content)->token == PIPE))));
}

int	check_syntax(t_data *data)
{
	t_list	*tmp;
	t_token	*token;

	tmp = data->tokens;
	while (tmp)
	{
		token = (t_token *)tmp->content;
		if ((tmp == data->tokens && ((t_token *)tmp->content)->token == PIPE)
			|| check_order(tmp))
		{
			ft_putstr_fd("minishell: syntax error.\n", STDERR_FILENO);
			return (0);
		}
		if (token)
		tmp = tmp->next;
	}
	return (1);
}
