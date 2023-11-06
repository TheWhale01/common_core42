/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrossett <jrossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 21:19:51 by hubretec          #+#    #+#             */
/*   Updated: 2022/09/15 13:48:11 by jrossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long long	ft_atoll(const char *nptr)
{
	long long	nb;
	int			minus;

	nb = 0;
	minus = 1;
	if (!nptr)
		return (0);
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '-')
	{
		minus = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
		nb = nb * 10 + (*(nptr++) - '0');
	return (nb * minus);
}

int	ft_atoll_ul(const char *nptr)
{
	unsigned long long	nb;

	nb = 0;
	if (!nptr)
		return (1);
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
		nb = nb * 10 + (*(nptr++) - '0');
	if (nb > 9223372036854775807)
		return (1);
	return (0);
}

unsigned long long	ft_atoll_ull(const char *nptr)
{
	unsigned long long	nb;
	int					n;

	n = 1;
	nb = 0;
	if (!nptr)
		return (1);
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			n = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
		nb = nb * 10 + (*(nptr++) - '0');
	return (nb * n);
}
