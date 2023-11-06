/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:12:14 by hubretec          #+#    #+#             */
/*   Updated: 2022/10/04 12:59:14 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

void	ft_putendl_fd(char const *s, int fd)
{
	char	*new;

	new = ft_strdup((char *)s);
	new = ft_strjoin_free_s1(new, "\n");
	write(fd, new, ft_strlen(new));
	free(new);
}
