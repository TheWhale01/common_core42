/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrossett <jrossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 12:18:58 by hubretec          #+#    #+#             */
/*   Updated: 2022/09/15 14:05:56 by jrossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 128
# endif

# define MAX_FD 256
# define INT_MAX 2147483647
# define INT_MIN -2147483648
# define DEC_BASE "0123456789"
# define HEX_BASE "0123456789abcdef"
# define HEX_BASE_M "0123456789ABCDEF"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int					abs(int n);
int					ft_tolower(int c);
int					ft_toupper(int c);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
int					ft_putchar(char c);
int					ft_min(int n, int m);
int					ft_max(int n, int m);
int					ft_putstr(char *str);
int					ft_whitespace(int c);
int					ft_lstsize(t_list *lst);
int					ft_atoi(const char *nptr);
int					ft_putchar_fd(char c, int fd);
int					ft_atoll_ul(const char *nptr);
int					ft_printf(const char *s, ...);
int					ft_is_in(char c, char *charset);
int					count_words(char const *s, char c);
int					ft_putstr_fd(char const *s, int fd);
int					ft_lstindex(t_list *node, t_list *lst);
int					ft_memcmp(void *s1, void *s2, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);

void				ft_swap(int *a, int *b);
void				ft_putnbr_fd(int n, int fd);
void				ft_bzero(void *s, size_t n);
void				print_addr(void *p0, int *len);
void				ft_putendl_fd(char const *s, int fd);
void				ft_striter(char *s, void (*f)(char *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
void				ft_lstadd_back(t_list **list, t_list *tmp);
void				ft_lstadd_front(t_list **alst, t_list *new);
void				ft_putnbr_base(int nb, char *base, int *len);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_putnbr_base_u(unsigned int nb, char *base, int *len);
void				ft_lstreplace_index(t_list *stack, t_list *new, int index);

char				*ft_itoa(int n);
char				*ft_strdup(char *src);
char				*get_next_line(int fd);
char				*ft_strndup(char *src, size_t n);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strcpy(char *dest, char *src);
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_strccpy(char *dest, char *src, char *charset);
char				*ft_strncpy(char *dest, char *src, unsigned int n);
char				*ft_strjoin_free_s1(char const *s1, char const *s2);
char				*ft_strjoin_free_s2(char const *s1, char const *s2);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_rstrstr(const char *haystack, const char *needle);
char				*ft_strjoin_free_s1_s2(char const *s1, char const *s2);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strnstr(const char *haystack,
						const char *needle, size_t n);

void				*ft_memset(void *s, int c, size_t n);
void				*ft_calloc(size_t nmemb, size_t size);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_memmove(void *dest, void *src, size_t n);
void				*ft_lstdelone(t_list *lst, void (*del)(void *));
void				*ft_lstclear(t_list **lst, void (*del)(void *));
void				*ft_memcpy(void *dest, const void *src, size_t n);

size_t				ft_strlen(char const *str);
size_t				ft_strlclen(const char *str, char *charset);
size_t				ft_strlcat(char *dst, char *src, size_t size);
size_t				ft_strlcpy(char *dest, char *src, size_t size);

t_list				*ft_lstnew(void *ptr);
t_list				*ft_lstmax(t_list *lst);
t_list				*ft_lstmin(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstpop(t_list **lst, t_list *node);
t_list				*ft_lst_find_at_index(t_list *lst, int index);
t_list				*ft_lstsearch(t_list **lst, void *data, size_t size);

char				**ft_split(char const *s, char c);

long long			ft_atoll(const char *nptr);

unsigned long long	ft_atoll_ull(const char *nptr);

#endif