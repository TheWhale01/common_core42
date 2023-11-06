/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 14:36:09 by hubretec          #+#    #+#             */
/*   Updated: 2022/02/01 20:25:28 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	sort_two(t_list **stack_a)
{
	sa_b(stack_a, "sa");
	return (1);
}

int	sort_three(t_list **stack_a)
{
	int	len;
	int	index;

	len = ft_lstsize(*stack_a);
	index = ft_lstindex(ft_lstmax(*stack_a), *stack_a);
	if (index < len / 2)
		ra_b(stack_a, "ra");
	else if (index < len - 1)
		rra_b(stack_a, "rra");
	if (!check_sorted(stack_a))
		sort_two(stack_a);
	return (1);
}

int	sort_four(t_list **stack_a, t_list **stack_b)
{
	int	len;
	int	index;

	len = ft_lstsize(*stack_a);
	index = ft_lstindex(ft_lstmin(*stack_a), *stack_a);
	if (index <= len / 2)
		while (index--)
			ra_b(stack_a, "ra");
	else
		while (index++ < len)
			rra_b(stack_a, "rra");
	pb(stack_a, stack_b, "pb");
	sort_three(stack_a);
	pa(stack_a, stack_b, "pa");
	return (1);
}

int	sort_five(t_list **stack_a, t_list **stack_b)
{
	int	len;
	int	index;

	len = ft_lstsize(*stack_a);
	index = ft_lstindex(ft_lstmin(*stack_a), *stack_a);
	if (index <= len / 2)
		while (index--)
			ra_b(stack_a, "ra");
	else
		while (index++ < len)
			rra_b(stack_a, "rra");
	pb(stack_a, stack_b, "pb");
	sort_four(stack_a, stack_b);
	pa(stack_a, stack_b, "pa");
	return (1);
}

int	simple_sort(t_list **stack_a, t_list **stack_b)
{
	int	len;

	(void)stack_b;
	len = ft_lstsize(*stack_a);
	if (len == 2)
		return (sort_two(stack_a));
	else if (len == 3)
		return (sort_three(stack_a));
	else if (len == 4)
		return (sort_four(stack_a, stack_b));
	else if (len == 5)
		return (sort_five(stack_a, stack_b));
	return (0);
}
