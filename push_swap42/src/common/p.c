/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 16:23:33 by hubretec          #+#    #+#             */
/*   Updated: 2022/02/01 20:21:26 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	pa(t_list **a, t_list **b, char *str)
{
	if (!*b)
		return ;
	ft_lstadd_front(a, pop_top(b));
	if (str)
		ft_putendl_fd(str, STDOUT);
}

void	pb(t_list **a, t_list **b, char *str)
{
	if (!*a)
		return ;
	ft_lstadd_front(b, pop_top(a));
	if (str)
		ft_putendl_fd(str, STDOUT);
}
