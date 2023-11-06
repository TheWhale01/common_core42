/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 16:41:36 by hubretec          #+#    #+#             */
/*   Updated: 2022/04/29 17:14:08 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_eat(t_philo *philos)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&philos->env->death);
	if (philos->env->limit_eat == -1)
	{
		pthread_mutex_unlock(&philos->env->death);
		return (0);
	}
	while (++i < philos->env->nb_philos)
	{
		if (philos[i].nb_eaten < philos[i].env->limit_eat)
		{
			pthread_mutex_unlock(&philos->env->death);
			return (0);
		}
	}
	pthread_mutex_unlock(&philos->env->death);
	return (1);
}

int	check_death(t_philo	*philo)
{
	pthread_mutex_lock(&philo->env->death);
	if ((get_ms() - philo->env->start_time) - philo->last_meal
		> (unsigned int)philo->env->time_to_die)
	{
		philo->env->died = 1;
		pthread_mutex_lock(&philo->env->write);
		printf("%d %d died\n", get_ms() - philo->env->start_time, philo->id + 1);
		pthread_mutex_unlock(&philo->env->write);
		pthread_mutex_unlock(&philo->env->death);
		return (1);
	}
	pthread_mutex_unlock(&philo->env->death);
	return (0);
}

int	dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->env->death);
	if (philo->env->died)
	{
		pthread_mutex_unlock(&philo->env->death);
		return (1);
	}
	pthread_mutex_unlock(&philo->env->death);
	return (0);
}

void	*live(void	*ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2)
		ft_sleep(philo->env->time_to_eat);
	while (!dead(philo) && (philo->env->limit_eat == -1
			|| philo->nb_eaten < philo->env->limit_eat))
	{
		philo_eat(philo);
		philo_sleep_think(philo, SLEEP);
		philo_sleep_think(philo, THINK);
	}
	return (NULL);
}

void	launch(t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < philos->env->nb_philos)
		pthread_create(&philos[i].thread, NULL, &live, &philos[i]);
	i = 0;
	while (1)
	{
		if (check_death(&philos[i]))
			break ;
		if (check_eat(philos))
			break ;
		i++;
		if (i == philos->env->nb_philos)
			i = 0;
	}
}
