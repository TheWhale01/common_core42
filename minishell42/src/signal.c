/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 07:43:41 by hubretec          #+#    #+#             */
/*   Updated: 2022/10/06 10:53:11 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint(void)
{
	if (g_global.heredoc_pid == -1)
	{
		printf("\n");
		if (!*(g_global.line))
		{
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
	}
	else
	{
		g_global.sigint = 1;
		free(g_global.fd_err);
		g_global.fd_err = NULL;
	}
	g_global.rtn_val = 130;
}

void	handler(int sig)
{
	if (sig == SIGINT)
		sigint();
	else if (sig == SIGQUIT)
	{
		if (!*(g_global.line))
			printf("\b\b  \b\b");
		else
			ft_putendl_fd("Quit (core dumped)", STDERR_FILENO);
	}
}

void	init_signals(void)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
}
