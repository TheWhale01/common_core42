/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:07:07 by hubretec          #+#    #+#             */
/*   Updated: 2022/09/28 11:22:59 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	varlen(char *str)
{
	int	i;

	i = -1;
	if (*str == '?')
		return (1);
	else if (!ft_isalpha(*str) && *str != '_')
		return (0);
	while (str[++i])
		if (!ft_isalnum(str[i]) && str[i] != '_')
			break ;
	return (i);
}

int	tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

t_list	*format(char *str)
{
	int		quote;
	char	*word;
	t_list	*lst;
	t_list	*node;

	quote = 0;
	lst = NULL;
	while (*str)
	{
		str = skip_spaces(str);
		if (!*str)
			break ;
		word = cut_word(str, &quote);
		if (!word)
			return (ft_lstclear(&lst, free));
		node = ft_lstnew(word);
		if (!node)
		{
			free(word);
			return (ft_lstclear(&lst, free));
		}
		ft_lstadd_back(&lst, node);
		str += ft_strlen(word);
	}
	return (lst);
}

void	tokenize(t_data *data, t_list *lst)
{
	t_list	*tmp;
	t_list	*node;

	tmp = lst;
	data->tokens = NULL;
	while (tmp)
	{
		node = choose_token(tmp, data->path);
		if (!node)
		{
			free_tokens(data->tokens);
			return ;
		}
		ft_lstadd_back(&data->tokens, node);
		tmp = tmp->next;
	}
	ft_lstclear(&lst, NULL);
}

void	expander(t_data *data)
{
	t_list	*tmp;
	t_list	*cut;

	tmp = data->tokens;
	while (tmp)
	{
		cut = cut_token(((t_token *)tmp->content)->str);
		replace_token(data, cut);
		join_token(tmp, cut);
		tmp = tmp->next;
	}
}
