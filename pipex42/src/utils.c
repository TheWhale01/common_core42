/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 13:39:05 by hubretec          #+#    #+#             */
/*   Updated: 2022/03/24 09:58:56 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "pipex.h"

void	exit_with_msg(char *str, int error)
{
	if (error)
		perror(str);
	else
		ft_putendl_fd(str, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	*free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
	return (NULL);
}

int	safe_open(char *filename, int mode, int perm)
{
	int	fd;

	fd = open(filename, mode, perm);
	if (fd == -1)
		exit_with_msg(filename, 1);
	return (fd);
}

void	write_pipe(int	*fd, char *limiter)
{
	char	*line;

	close(fd[0]);
	while (1)
	{
		ft_putstr_fd("pipex heredoc> ", STDIN_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (!ft_strncmp(line, limiter, ft_strlen(limiter)))
		{
			free(line);
			exit(EXIT_SUCCESS);
		}
		write(fd[1], line, ft_strlen(line));
		free(line);
	}
}
