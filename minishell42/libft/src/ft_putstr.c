/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:12:41 by hubretec          #+#    #+#             */
/*   Updated: 2022/09/28 13:46:52 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

int	ft_putstr_fd(char const *s, int fd)
{
	int	len;

	len = write(fd, s, ft_strlen(s));
	return (len);
}

int	ft_putstr(char *str)
{
	int	len;

	len = write(1, str, ft_strlen(str));
	return (len);
}
