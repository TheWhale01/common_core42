/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 18:32:42 by hubretec          #+#    #+#             */
/*   Updated: 2022/02/17 10:37:11 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "push_swap.h"

int	do_op(char *line, t_list **stack_a, t_list **stack_b)
{
	if (!ft_strcmp(line, "sa\n"))
		sa_b(stack_a, NULL);
	else if (!ft_strcmp(line, "sb\n"))
		sa_b(stack_b, NULL);
	else if (!ft_strcmp(line, "ss\n"))
		ss(stack_a, stack_b, NULL);
	else if (!ft_strcmp(line, "pa\n"))
		pa(stack_a, stack_b, NULL);
	else if (!ft_strcmp(line, "pb\n"))
		pb(stack_a, stack_b, NULL);
	else if (!ft_strcmp(line, "ra\n"))
		ra_b(stack_a, NULL);
	else if (!ft_strcmp(line, "rb\n"))
		ra_b(stack_b, NULL);
	else if (!ft_strcmp(line, "rr\n"))
		rr(stack_a, stack_b, NULL);
	else if (!ft_strcmp(line, "rra\n"))
		rra_b(stack_a, NULL);
	else if (!ft_strcmp(line, "rrb\n"))
		rra_b(stack_b, NULL);
	else if (!ft_strcmp(line, "rrr\n"))
		rrr(stack_a, stack_b, NULL);
	else
		return (0);
	return (1);
}

int	checker(t_list **stack_a, t_list **stack_b)
{
	char	*line;

	while (1)
	{
		line = get_next_line(STDIN);
		if (!line)
			break ;
		if (!do_op(line, stack_a, stack_b))
		{
			free(line);
			return (0);
		}
		free(line);
	}
	if (!check_sorted(stack_a) && *stack_b)
		return (0);
	return (1);
}
