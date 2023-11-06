/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pop.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 15:43:00 by hubretec          #+#    #+#             */
/*   Updated: 2022/01/24 15:25:20 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_list	*pop_bottom(t_list **stack)
{
	t_list	*tmp;
	t_list	*pop;

	tmp = *stack;
	pop = ft_lstlast(*stack);
	while (tmp->next->next)
		tmp = tmp->next;
	tmp->next = NULL;
	return (pop);
}

t_list	*pop_top(t_list	**stack)
{
	t_list	*pop;

	pop = *stack;
	*stack = (*stack)->next;
	pop->next = NULL;
	return (pop);
}
