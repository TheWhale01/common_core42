/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 16:02:54 by hubretec          #+#    #+#             */
/*   Updated: 2022/03/24 14:31:35 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "pipex.h"

void	child_p(char **av, char **env, int *fd)
{
	int	infile;

	infile = safe_open(av[1], O_RDONLY, 0644);
	dup2(fd[1], STDOUT_FILENO);
	dup2(infile, STDIN_FILENO);
	close(fd[0]);
	if (!exec_cmd(av[2], env))
	{
		close(infile);
		exit(EXIT_FAILURE);
	}
	close(infile);
}

void	main_p(char **av, char **env, int *fd)
{
	int	outfile;

	outfile = safe_open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(fd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(fd[1]);
	exec_cmd(av[3], env);
	close(outfile);
}

int	main(int ac, char **av, char **env)
{
	int		fd[2];
	int		pid;

	if (!env || !*env)
		exit_with_msg("Environment not found.", 0);
	if (ac != 5)
		exit_with_msg("Wrong number of args.", 0);
	if (pipe(fd))
		exit_with_msg("pipe", 1);
	pid = fork();
	if (pid == -1)
		exit_with_msg("fork", 1);
	if (!pid)
		child_p(av, env, fd);
	waitpid(pid, NULL, 0);
	main_p(av, env, fd);
	return (0);
}
