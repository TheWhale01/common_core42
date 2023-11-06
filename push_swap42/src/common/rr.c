/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rr.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 23:22:33 by hubretec          #+#    #+#             */
/*   Updated: 2022/02/01 20:23:12 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rra_b(t_list **stack, char *str)
{
	ft_lstadd_front(stack, pop_bottom(stack));
	if (str)
		ft_putendl_fd(str, STDOUT);
}

void	rrr(t_list **a, t_list **b, char *str)
{
	rra_b(a, NULL);
	rra_b(b, NULL);
	if (str)
		ft_putendl_fd("rrr", STDOUT);
}
