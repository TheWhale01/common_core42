/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 13:40:27 by hubretec          #+#    #+#             */
/*   Updated: 2021/12/08 16:40:33 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdint.h>
#include "ft_printf.h"

void	ft_putchar(char c, int *len)
{
	write(1, &c, 1);
	*len += 1;
}

void	ft_putstr(char *str, int *len)
{
	if (!str)
	{
		write(1, "(null)", 6);
		*len += 6;
		return ;
	}
	while (*str)
	{
		write(1, str++, 1);
		*len += 1;
	}
}

char	hex_digit(int v)
{
	if (v >= 0 && v < 10)
		return ('0' + v);
	return ('a' + v - 10);
}

void	print_addr(void *p0, int *len)
{
	int			i;
	uintptr_t	p;

	if (!p0)
	{
		ft_putstr("0x0", len);
		return ;
	}
	p = (uintptr_t)p0;
	ft_putstr("0x", len);
	i = (sizeof(p) << 3) - 4;
	while (hex_digit((p >> i) & 0xf) == '0' && i >= 0)
		i -= 4;
	while (i >= 0)
	{
		ft_putchar(hex_digit((p >> i) & 0xf), len);
		i -= 4;
	}
}
