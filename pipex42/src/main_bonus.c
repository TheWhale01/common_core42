/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 16:02:54 by hubretec          #+#    #+#             */
/*   Updated: 2022/03/24 14:39:35 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "pipex.h"

void	child_p(char *cmd, char **env, int infile, char *filename)
{
	int	pid;
	int	fd[2];

	if (pipe(fd) == -1)
		exit_with_msg("pipe", 1);
	pid = fork();
	if (pid == -1)
		exit_with_msg("fork", 1);
	else if (!pid)
	{
		close(fd[0]);
		if (!infile)
			exit_with_msg(filename, 1);
		dup2(fd[1], STDOUT_FILENO);
		if (!exec_cmd(cmd, env))
			exit(EXIT_FAILURE);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

void	main_p(char **av, char **env, int *files, char *filename)
{
	while (*(av + 2))
		child_p(*(av++), env, files[0], filename);
	dup2(files[1], STDOUT_FILENO);
	exec_cmd(*av, env);
	if (files[0] != -1)
		close(files[0]);
	close(files[1]);
}

void	here_doc(char *limiter, int ac)
{
	int		pid;
	int		fd[2];

	if (ac < 6)
		exit_with_msg("Wrong number of args.", 0);
	if (pipe(fd) == -1)
		exit_with_msg("pipe", 1);
	pid = fork();
	if (!pid)
		write_pipe(fd, limiter);
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		wait(NULL);
	}
}

int	main(int ac, char **av, char **env)
{
	int		i;
	int		files[2];

	if (!env || !*env)
		exit_with_msg("Environment not found.", 0);
	if (ac < 5)
		exit_with_msg("Wrong number of args.", 0);
	i = 3;
	if (!ft_strncmp(av[1], "here_doc", ft_strlen(av[1])))
	{
		files[0] = -1;
		files[1] = safe_open(av[ac - 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
		here_doc(av[2], ac);
	}
	else
	{
		i = 2;
		files[0] = open(av[1], O_RDONLY, 0644);
		if (files[0] == -1)
			files[0] = 0;
		files[1] = safe_open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		dup2(files[0], STDIN_FILENO);
	}
	main_p(&av[i], env, files, av[1]);
	return (0);
}
