/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 12:12:05 by hubretec          #+#    #+#             */
/*   Updated: 2022/10/05 09:01:59 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path_cmd(char *cmd, char **env)
{
	char	*tmp;
	char	*path_cmd;

	if (!cmd)
		return (NULL);
	if (!access(cmd, F_OK) && (*cmd == '/' || !ft_strncmp(cmd, "./", 2)
			|| cmd[ft_strlen(cmd) - 1] == '/'))
		return (ft_strdup(cmd));
	while (env && *env)
	{
		tmp = ft_strdup(*env);
		path_cmd = ft_strjoin_free_s1(tmp, cmd);
		if (!access(path_cmd, F_OK))
			return (path_cmd);
		free(path_cmd);
		env++;
	}
	return (NULL);
}

void	exec_builtin(char **args, t_data *data)
{
	if (!ft_strcmp(args[0], "env"))
		ft_env(data);
	else if (!ft_strcmp(args[0], "exit"))
		ft_exit(data, "exit", EXIT_SUCCESS, args);
	else if (!ft_strcmp(args[0], "cd"))
		ft_cd(data, args);
	else if (!ft_strcmp(args[0], "pwd"))
		ft_pwd(data);
	else if (!ft_strcmp(args[0], "unset"))
		ft_unset(data, args);
	else if (!ft_strcmp(args[0], "export"))
		ft_export(data, args);
	else if (!ft_strcmp(args[0], "echo"))
		ft_echo(args);
}

void	exec_cmd(char **args, t_data *data)
{
	int			code;
	char		*msg;
	char		*path;
	char		**env;

	env = list_to_tab(data->envp);
	path = get_path_cmd(*args, data->path);
	exec_errors(path, *args, &msg, &code);
	if (!code && execve(path, args, env) == -1)
		perror(args[0]);
	free(env);
	free(path);
	free_pipeline(data);
	if (code && *args)
		msg = ft_strjoin(*args, msg);
	exit_cmd(code, data, msg, args);
	free(msg);
	exit(code);
}

void	wait_set_rtn_value(pid_t pid)
{
	waitpid(pid, &g_global.rtn_val, WUNTRACED);
	if (WIFEXITED(g_global.rtn_val))
		g_global.rtn_val = WEXITSTATUS(g_global.rtn_val);
	else if (WIFSIGNALED(g_global.rtn_val))
		g_global.rtn_val = 128 + (WTERMSIG(g_global.rtn_val));
	else
		g_global.rtn_val = 0;
}

void	exec(t_data *data)
{
	int		pid;
	char	**args;

	make_redirs(data, data->tokens);
	if (g_global.fd_err || g_global.sigint)
		return (restore_redirs(data));
	args = get_args(skip_redirs(data->tokens));
	if (args && is_builtin(args[0]))
		exec_builtin(args, data);
	else if (args)
	{
		pid = fork();
		if (!pid)
			exec_cmd(args, data);
		else
			wait_set_rtn_value(pid);
	}
	if (g_global.rtn_val == 139)
		ft_putendl_fd("Segmentation fault (core dumped).", STDERR_FILENO);
	free(args);
	restore_redirs(data);
}
