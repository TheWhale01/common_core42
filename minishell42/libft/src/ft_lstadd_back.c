/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 13:26:49 by hubretec          #+#    #+#             */
/*   Updated: 2022/09/28 10:34:22 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **list, t_list *tmp)
{
	t_list	*end;

	if (!list)
		return ;
	if (!(*list))
	{
		*list = tmp;
		return ;
	}
	end = *list;
	while (end->next)
		end = end->next;
	end->next = tmp;
}
