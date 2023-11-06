/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 14:39:15 by hubretec          #+#    #+#             */
/*   Updated: 2022/02/01 13:06:13 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "push_swap.h"

int	optimize(int index, int len)
{
	if (index > len / 2)
		return ((len - index) * -1);
	return (index);
}

t_pos	get_pos(t_list *node, t_list *stack_a, t_list *stack_b)
{
	t_pos	pos;
	t_list	*max;
	t_list	*tmp;

	pos.stack_a = 0;
	max = ft_lstmax(stack_a);
	tmp = stack_a;
	while (tmp->next)
	{
		if ((*(int *)tmp->next->content > *(int *)node->content
				&& (*(int *)tmp->content < *(int *)node->content
					|| *(int *)tmp->content == *(int *)max->content))
			|| (*(int *)tmp->next->content < *(int *)node->content
				&& *(int *)node->content > *(int *)max->content
				&& *(int *)tmp->content == *(int *)max->content))
		{
			pos.stack_a = optimize(ft_lstindex(tmp->next, stack_a),
					ft_lstsize(stack_a));
			break ;
		}
		tmp = tmp->next;
	}
	pos.stack_b = optimize(ft_lstindex(node, stack_b), ft_lstsize(stack_b));
	return (pos);
}

t_list	*cost(t_pos *pos, t_list *stack_a, t_list *stack_b)
{
	int		min_pos;
	t_pos	tmp_pos;
	t_list	*tmp;
	t_list	*min;

	min_pos = INT_MAX;
	tmp = stack_b;
	while (tmp)
	{
		tmp_pos = get_pos(tmp, stack_a, stack_b);
		if (abs(tmp_pos.stack_a) + abs(tmp_pos.stack_b) < min_pos)
		{
			min_pos = abs(tmp_pos.stack_a) + abs(tmp_pos.stack_b);
			min = tmp;
			*pos = tmp_pos;
		}
		tmp = tmp->next;
	}
	return (min);
}
