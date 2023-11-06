/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 16:28:07 by hubretec          #+#    #+#             */
/*   Updated: 2022/02/01 20:22:58 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ra_b(t_list **stack, char *str)
{
	ft_lstadd_back(stack, pop_top(stack));
	if (str)
		ft_putendl_fd(str, STDOUT);
}

void	rr(t_list **a, t_list **b, char *str)
{
	ra_b(a, NULL);
	ra_b(b, NULL);
	if (str)
		ft_putendl_fd(str, STDOUT);
}
