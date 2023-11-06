/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 20:52:58 by hubretec          #+#    #+#             */
/*   Updated: 2021/12/03 14:36:23 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

int	ft_strlen(const char *str, int start, char c)
{
	int	i;

	i = start;
	if (!str)
		return (0);
	while (str[i] && str[i] != c)
		i++;
	return (i - start);
}

int	line_len(char *str, int start)
{
	int	i;

	i = start;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	return (i - start);
}

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	x;

	i = -1;
	x = c;
	if (!s)
		return (0);
	while (s[++i])
		if (s[i] == x)
			return ((char *)&s[i]);
	if (s[i] == x)
		return ((char *)&s[i]);
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		s1len;
	char	*str;

	s1len = ft_strlen(s1, 0, 0);
	str = (char *)malloc(sizeof(char) * (s1len + ft_strlen(s2, 0, 0) + 1));
	if (!str)
		return (0);
	i = 0;
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[i - s1len])
	{
		str[i] = s2[i - s1len];
		i++;
	}
	str[i] = '\0';
	if (s1)
		free((char *)s1);
	return (str);
}
