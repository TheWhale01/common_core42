/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:24:19 by hubretec          #+#    #+#             */
/*   Updated: 2022/04/29 17:41:17 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check(int ac, char **av)
{
	int			i;
	long long	nb;

	if (ac < 5 || ac > 6)
		return (0);
	i = 0;
	while (++i < ac)
	{
		nb = ft_atoll(av[i]);
		if (ft_strlen(av[i]) > 10
			|| !ft_is_number(av[i]) || (nb <= 0 && nb > INT_MAX))
			return (0);
		if (i == 1 && (nb <= 0 || nb > 200))
			return (0);
	}
	return (1);
}

void	ft_sleep(unsigned int ms)
{
	int	start;

	start = get_ms();
	while ((get_ms() - start) < ms)
		usleep(ms / 10);
}

void	print_state(t_philo	*philo)
{
	if (dead(philo))
		return ;
	pthread_mutex_lock(&philo->env->write);
	if (philo->state == EAT)
		printf("%d %d is eating\n",
			get_ms() - philo->env->start_time, philo->id + 1);
	else if (philo->state == SLEEP)
		printf("%d %d is sleeping\n",
			get_ms() - philo->env->start_time, philo->id + 1);
	else if (philo->state == THINK)
		printf("%d %d is thinking\n",
			get_ms() - philo->env->start_time, philo->id + 1);
	else if (philo->state == FORKS)
		printf("%d %d has taken a fork\n",
			get_ms() - philo->env->start_time, philo->id + 1);
	pthread_mutex_unlock(&philo->env->write);
}

void	*free_philos(t_philo	*philos)
{
	int	i;

	i = -1;
	while (++i < philos->env->nb_philos)
		pthread_join(philos[i].thread, NULL);
	i = -1;
	while (++i < philos->env->nb_philos)
		pthread_mutex_destroy(&philos->env->forks[i]);
	pthread_mutex_destroy(&philos->env->death);
	pthread_mutex_destroy(&philos->env->write);
	free(philos->env->forks);
	free(philos->env);
	free(philos);
	return (NULL);
}

unsigned int	get_ms(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}
