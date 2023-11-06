/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 15:01:10 by hubretec          #+#    #+#             */
/*   Updated: 2021/12/08 10:33:42 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"

void	ft_putnbr_base(int nb, char *base, int *len)
{
	int				base_len;
	unsigned int	nbr;

	base_len = ft_strlen(base);
	if (nb < 0)
	{
		nbr = nb * -1;
		*len += 1;
		write(1, "-", 1);
	}
	else
		nbr = nb;
	if (nbr / base_len)
		ft_putnbr_base(nbr / base_len, base, len);
	write(1, &base[nbr % base_len], 1);
	*len += 1;
}

void	ft_putnbr_base_u(unsigned int nb, char *base, int *len)
{
	int		base_len;

	base_len = ft_strlen(base);
	if (nb / base_len)
		ft_putnbr_base(nb / base_len, base, len);
	write(1, &base[nb % base_len], 1);
	*len += 1;
}
