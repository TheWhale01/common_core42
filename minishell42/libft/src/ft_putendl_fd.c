/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:12:14 by hubretec          #+#    #+#             */
/*   Updated: 2022/09/28 14:54:43 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

void	ft_putendl_fd(char const *s, int fd)
{
	int		len;
	char	*new;

	len = ft_strlen(s);
	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return ;
	new = ft_strncpy(new, (char *)s, len);
	new[len] = '\n';
	write(fd, new, len + 1);
	free(new);
}
