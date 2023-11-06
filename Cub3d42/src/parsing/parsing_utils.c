/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrossett <jrossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 01:36:13 by jrossett          #+#    #+#             */
/*   Updated: 2022/10/26 01:36:14 by jrossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strdup_2(char *src, char c)
{
	int		i;
	char	*string;

	i = 0;
	if (!src)
		return (NULL);
	if (!c)
		c = '\0';
	while (src[i] && src[i] != c)
		i++;
	string = malloc(sizeof(char) * (i + 1));
	if (!string)
		return (0);
	i = -1;
	while (src[++i] != c)
		string[i] = src[i];
	string[i] = '\0';
	return (string);
}

int	ft_atoi_3(const char *nptr, int nb, int minus)
{
	if (*nptr < '0' || *nptr > '9')
		return (-1);
	while (*nptr >= '0' && *nptr <= '9')
	{
		nb = nb * 10 + (*(nptr++) - '0');
		if (nb > 999)
			return (-1);
	}
	while (*nptr)
	{
		if (*nptr != ' ')
			return (-1);
		nptr++;
	}
	return (nb * minus);
}

int	ft_atoi_2(const char *nptr)
{
	int	nb;
	int	minus;

	nb = 0;
	minus = 1;
	while (*nptr == 32)
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			minus = -1;
		nptr++;
	}
	return (ft_atoi_3(nptr, nb, minus));
}

int	ft_asign_rgb(t_elem *elem)
{
	elem->fr = ft_atoi_2(elem->f[0]);
	elem->fg = ft_atoi_2(elem->f[1]);
	elem->fb = ft_atoi_2(elem->f[2]);
	elem->cr = ft_atoi_2(elem->c[0]);
	elem->cg = ft_atoi_2(elem->c[1]);
	elem->cb = ft_atoi_2(elem->c[2]);
	if ((elem->fr < 0 || elem->fr > 255) || (elem->fg < 0 || elem->fg > 255)
		|| (elem->fb < 0 || elem->fb > 255) || (elem->cr < 0 || elem->cr > 255)
		|| (elem->cg < 0 || elem->cg > 255)
		|| (elem->cb < 0 || elem->cb > 255))
		return (1);
	return (0);
}

int	ft_verif_elem(t_elem *elem)
{
	if (!elem->no || !elem->so || !elem->ea || !elem->we || !elem->c
		|| !elem->f)
		return (1);
	if (elem->c[0] == NULL || elem->c[1] == NULL || elem->c[2] == NULL
		|| elem->f[0] == NULL || elem->f[1] == NULL
		|| elem->f[1] == NULL || elem->f[2] == NULL)
		return (1);
	if (ft_asign_rgb(elem))
		return (1);
	return (0);
}
