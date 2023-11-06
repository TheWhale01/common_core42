/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 14:19:54 by hubretec          #+#    #+#             */
/*   Updated: 2022/03/24 14:24:01 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 128
# endif

# define MAX_FD 254

int		ft_putstr(char const *s);
int		exec_cmd(char *cmd, char **env);
int		ft_putstr_fd(char const *s, int fd);
int		safe_open(char *filename, int mode, int perm);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

void	exit_with_msg(char *str, int error);
void	write_pipe(int	*fd, char *limiter);
void	ft_putendl_fd(char const *s, int fd);

char	*ft_strdup(char *src);
char	*get_next_line(int fd);
char	*ft_strchr(const char *s, int c);
char	*get_path_cmd(char *cmd, char **env);
char	*ft_strjoin(char const *s1, char const *s2);

void	*free_tab(char **tab);

char	**get_path_env(char **env);
char	**ft_split(char const *s, char c);

size_t	ft_strlen(const char *str);

#endif