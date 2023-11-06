/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 09:03:22 by hubretec          #+#    #+#             */
/*   Updated: 2021/12/03 15:10:40 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

int	mem_empty(char *memory)
{
	while (*memory)
		if (*(memory++) != 127)
			return (0);
	return (1);
}

char	*get_memory(int fd, int *bytes, char *memory)
{
	char	*tmp;

	tmp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!tmp)
		return (NULL);
	*tmp = '\0';
	while (!ft_strchr(tmp, '\n') && *bytes)
	{
		*bytes = read(fd, tmp, BUFFER_SIZE);
		if (*bytes < 0)
		{
			free(tmp);
			if (memory)
				free(memory);
			return (NULL);
		}
		if (!*bytes && !*tmp)
			break ;
		tmp[*bytes] = '\0';
		memory = ft_strjoin(memory, tmp);
	}
	free(tmp);
	return (memory);
}

char	*fill_line(char *memory)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (memory && memory[i] == 127)
		i++;
	line = malloc(sizeof(char) * (line_len(memory, i) + 1));
	if (!line)
		return (NULL);
	j = 0;
	while (memory[i] && memory[i] != '\n')
	{
		line[j++] = memory[i];
		memory[i++] = 127;
	}
	if (memory[i] == '\n')
	{
		line[j++] = '\n';
		memory[i++] = 127;
	}
	line[j] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	int			bytes;
	char		*line;
	static char	*memory;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	bytes = 1;
	memory = get_memory(fd, &bytes, memory);
	if (!memory)
		return (NULL);
	else if (!bytes && !*memory)
	{
		free(memory);
		return (NULL);
	}
	line = fill_line(memory);
	if (mem_empty(memory))
	{
		free(memory);
		memory = 0;
	}
	return (line);
}

//#include <fcntl.h>
//#include <stdio.h>
//int main(int ac, char **av)
//{
//	int fd;
//	char *line;
//
//	if (ac != 2)
//		fd = 0;
//	else
//		fd = open(av[1], O_RDONLY);
//	while (1)
//	{
//		line = get_next_line(fd);
//		if (!line)
//			return (0);
//		printf("%s", line);
//		free(line);
//	}
//	return (0);
//}
