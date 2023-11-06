/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 04:29:14 by jrossett          #+#    #+#             */
/*   Updated: 2022/10/05 13:56:31 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <dirent.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <readline/history.h>
# include <readline/readline.h>

enum	e_token
{
	CMD,
	PIPE,
	WORD,
	REDIR_IN,
	REDIR_OUT,
	D_REDIR_IN,
	D_REDIR_OUT,
};

typedef struct s_token
{
	int		token;
	char	*str;
}	t_token;

typedef struct s_pipeline
{
	int		nb_pipes;
	int		nb_children;
	int		**pipes;
	pid_t	*children;
}	t_pipeline;

typedef struct s_data
{
	int			fd_in;
	int			fd_out;
	char		*pwd;
	char		*line;
	char		**path;
	t_list		*envp;
	t_list		*tokens;
	t_pipeline	pipeline;
}	t_data;

typedef struct s_global
{
	int		fd[2];
	int		sigint;
	int		rtn_val;
	int		heredoc_pid;
	char	*eof;
	char	*fd_err;
	char	**line;
}	t_global;

int		varlen(char *str);
int		tablen(char **tab);
int		is_redir(char *str);
int		get_quote(char *str);
int		is_builtin(char *str);
int		is_dir(char *filename);
int		check_quotes(char *str);
int		ft_len_double(char **tab);
int		check_syntax(t_data *data);
int		get_nb_tokens(t_list *tokens, int e_token);

void	handler(int sig);
void	exec(t_data *data);
void	init_signals(void);
void	heredoc(t_data *data);
void	expander(t_data *data);
void	pipeline(t_data *data);
void	ft_norme_exit(t_data *data);
void	free_pipeline(t_data *data);
void	free_tokens(t_list *tokens);
void	restore_redirs(t_data *data);
void	wait_set_rtn_value(pid_t pid);
void	safe_exit(t_data *data, char *str);
void	tokenize(t_data *data, t_list *lst);
void	exec_cmd(char **args, t_data *data);
void	join_token(t_list *token, t_list *cut);
void	exec_builtin(char **args, t_data *data);
void	replace_token(t_data *data, t_list *cut);
void	make_redirs(t_data *data, t_list *start);
void	exec_errors(char *path, char *args, char **msg, int *code);

void	*free_tab(char	**tab);

char	*skip_spaces(char *str);
char	*ft_prompt(t_data *data);
char	*remove_quotes(char *str);
char	*get_prompt(t_data *data);
char	*file_error(char *filename);
char	*cut_word(char *str, int *quote);
char	*search_env(char *str, t_data *data);
char	*replace_var(t_data *data, t_list *token, char *str);

t_list	*format(char *str);
t_list	*cut_token(char *str);
t_list	*skip_redirs(t_list	*tokens);
t_list	*skip_pipes(t_list *tokens, int pos);
t_list	*choose_token(t_list *node, char **path);
t_list	*search_token(t_list *tokens, int search, int pipe);

char	**list_to_tab(t_list *lst);
char	**get_path_env(char *path);
char	**get_args(t_list *tokens);

// -----------------------------BUILTINS-----------------------------

int		vnb(char *s);
int		ft_echo(char **arg);
int		ft_pwd(t_data *data);
int		ft_cd(t_data *data, char **arg);
int		ft_unset(t_data *data, char **arg);
int		ft_export(t_data *data, char **arg);
int		ft_lstexport(t_data *data, char *str);
int		ft_path_cd(char **arg, char **path, t_data *data);
int		ft_verif_norme(char **arg, char **path, t_data *data);
int		ft_exit(t_data *data, char *str, int exit_code, char **args);

void	ft_env(t_data *data);
void	ft_perror(char *join);
void	update_pwd(t_data *data);
void	free_pipes(t_data *data);
void	close_pipes(t_data *data);
void	ft_list_sort(t_list *list);
void	exit_cmd(int exit_code, t_data *data, char *str, char **args);
void	ft_numeric(int exit_code, t_data *data, char *str, char **args);

t_list	*create_list(char **envp);

extern t_global	g_global;

#endif
