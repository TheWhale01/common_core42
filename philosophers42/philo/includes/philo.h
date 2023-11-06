/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 16:39:54 by hubretec          #+#    #+#             */
/*   Updated: 2022/04/29 17:39:58 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define INT_MAX 2147483647

enum
{
	EAT,
	SLEEP,
	THINK,
	FORKS,
};

typedef struct s_env
{
	int				died;
	int				nb_philos;
	int				limit_eat;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	unsigned int	start_time;
	pthread_mutex_t	death;
	pthread_mutex_t	write;
	pthread_mutex_t	*forks;
}	t_env;

typedef struct s_philo
{
	int			id;
	int			state;
	int			nb_eaten;
	int			last_meal;
	t_env		*env;
	pthread_t	thread;
}	t_philo;

int				dead(t_philo *philo);
int				ft_is_number(char *str);
int				check(int ac, char **av);

void			launch(t_philo *philos);
void			philo_eat(t_philo *philo);
void			ft_sleep(unsigned int ms);
void			print_state(t_philo	*philo);
void			philo_sleep_think(t_philo *philo, int state);

void			*free_philos(t_philo *philos);

size_t			ft_strlen(const char *str);

t_philo			*init(int ac, char **av);

long long		ft_atoll(const char *nptr);

unsigned int	get_ms(void);

#endif