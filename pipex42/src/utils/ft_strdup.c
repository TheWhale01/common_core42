/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:14:20 by hubretec          #+#    #+#             */
/*   Updated: 2022/02/17 12:09:02 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "pipex.h"

char	*ft_strdup(char *src)
{
	int		i;
	char	*string;

	string = malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (!string)
		return (0);
	i = -1;
	while (src[++i] != '\0')
		string[i] = src[i];
	string[i] = '\0';
	return (string);
}
