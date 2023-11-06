/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 14:39:26 by hubretec          #+#    #+#             */
/*   Updated: 2022/02/01 20:26:04 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	smart_rotate(t_pos *pos, t_list **stack_a, t_list **stack_b)
{
	if (pos->stack_a * pos->stack_b <= 0)
		return ;
	while (pos->stack_a > 0 && pos->stack_b > 0)
	{
		rr(stack_a, stack_b, "rr");
		pos->stack_a--;
		pos->stack_b--;
	}
	while (pos->stack_a < 0 && pos->stack_b < 0)
	{
		rrr(stack_a, stack_b, "rrr");
		pos->stack_a++;
		pos->stack_b++;
	}
}

void	place_in_stack(t_pos *pos, t_list **stack_a, t_list **stack_b)
{
	int		len;

	len = ft_lstsize(*stack_a);
	smart_rotate(pos, stack_a, stack_b);
	if (len == 1)
		pa(stack_a, stack_b, "pa");
	while (pos->stack_a-- > 0)
		ra_b(stack_a, "ra");
	while (++pos->stack_a < 0)
		rra_b(stack_a, "rra");
	while (pos->stack_b-- > 0)
		ra_b(stack_b, "rb");
	while (++pos->stack_b < 0)
		rra_b(stack_b, "rrb");
	if (len != 1)
		pa(stack_a, stack_b, "pa");
}

void	solve(t_list **stack_a, t_list **stack_b)
{
	int		len;
	int		index;
	t_pos	pos;

	len = ft_lstsize(*stack_a);
	push_to_b(stack_a, stack_b);
	while (*stack_b)
	{
		cost(&pos, *stack_a, *stack_b);
		place_in_stack(&pos, stack_a, stack_b);
	}
	index = ft_lstindex(ft_lstmin(*stack_a), *stack_a);
	if (index)
	{
		if (index <= len / 2)
			while (index--)
				ra_b(stack_a, "ra");
		else
			while (index++ < len)
				rra_b(stack_a, "rra");
	}
}
