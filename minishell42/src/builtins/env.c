/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 21:06:23 by teambersaw        #+#    #+#             */
/*   Updated: 2022/09/16 10:23:49 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_path_env(char *path)
{
	int		i;
	char	**new;

	i = -1;
	if (!path)
		return (NULL);
	new = ft_split(path, ':');
	while (new[++i])
		new[i] = ft_strjoin_free_s1(new[i], "/");
	free(path);
	return (new);
}

char	*special_case(char **str)
{
	if (**str == '$' && *(*str + 1) != '_' && *(*str + 1) != '?'
		&& !ft_isalnum(*(*str + 1)))
		return (ft_strdup("$"));
	else if (**str == '$')
		(*str)++;
	if (**str == '?')
		return (ft_itoa(g_global.rtn_val));
	else if (ft_isdigit(**str))
		return (NULL);
	return (*str);
}

char	*search_env(char *str, t_data *data)
{
	int		strlen;
	int		envlen;
	char	*found;
	char	*sp_case;
	t_list	*tmp;

	sp_case = special_case(&str);
	if (sp_case != str)
		return (sp_case);
	tmp = data->envp;
	while (tmp)
	{
		envlen = ft_strlclen(tmp->content, "=");
		strlen = varlen(str);
		if (envlen == strlen && !ft_strncmp(str, (char *)tmp->content, envlen))
		{
			found = ft_strchr(tmp->content, '=');
			if (!found)
				return (NULL);
			return (ft_strdup(found + 1));
		}
		tmp = tmp->next;
	}
	return (NULL);
}

t_list	*create_list(char **envp)
{
	char	*str;
	t_list	*list;
	t_list	*tmp;
	int		i;

	i = 1;
	if (!envp || !*envp || !(**envp))
	{
		list = ft_lstnew(ft_strdup("OLDPWD"));
		tmp = ft_lstnew(ft_strjoin_free_s2("PWD=", getcwd(NULL, 0)));
		ft_lstadd_back(&list, tmp);
		tmp = ft_lstnew(ft_strdup("SHLVL=1"));
		ft_lstadd_back(&list, tmp);
		return (list);
	}
	str = ft_strdup(envp[0]);
	list = ft_lstnew(str);
	while (envp[i])
	{
		str = ft_strdup(envp[i]);
		tmp = ft_lstnew(str);
		ft_lstadd_back(&list, tmp);
		i++;
	}
	return (list);
}

void	ft_env(t_data *data)
{
	t_list	*tmp;

	g_global.rtn_val = 0;
	tmp = data->envp;
	if (!tmp || !tmp->content)
		return ;
	while (tmp)
	{
		if (ft_strchr((char *)tmp->content, '='))
			printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
}
