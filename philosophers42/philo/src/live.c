/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 16:41:08 by hubretec          #+#    #+#             */
/*   Updated: 2022/04/29 17:02:05 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	philo->state = FORKS;
	if (philo->id == philo->env->nb_philos - 1)
	{
		pthread_mutex_lock(&philo->env->forks[0]);
		print_state(philo);
		if (philo->env->nb_philos == 1)
		{
			ft_sleep(philo->env->time_to_die);
			pthread_mutex_unlock(&philo->env->forks[0]);
			return ;
		}
		pthread_mutex_lock(&philo->env->forks[philo->id]);
		print_state(philo);
	}
	else
	{
		pthread_mutex_lock(&philo->env->forks[philo->id]);
		print_state(philo);
		pthread_mutex_lock(&philo->env->forks[philo->id + 1]);
		print_state(philo);
	}
}

void	drop_forks(t_philo *philo)
{
	if (philo->env->nb_philos == 1)
		return ;
	if (philo->id == philo->env->nb_philos - 1)
	{
		pthread_mutex_unlock(&philo->env->forks[0]);
		pthread_mutex_unlock(&philo->env->forks[philo->id]);
	}
	else
	{
		pthread_mutex_unlock(&philo->env->forks[philo->id]);
		pthread_mutex_unlock(&philo->env->forks[philo->id + 1]);
	}
}

void	philo_eat(t_philo *philo)
{
	take_forks(philo);
	philo->state = EAT;
	print_state(philo);
	pthread_mutex_lock(&philo->env->death);
	philo->nb_eaten++;
	philo->last_meal = get_ms() - philo->env->start_time;
	pthread_mutex_unlock(&philo->env->death);
	ft_sleep(philo->env->time_to_eat);
	drop_forks(philo);
}

void	philo_sleep_think(t_philo *philo, int state)
{
	philo->state = state;
	print_state(philo);
	if (state == SLEEP && philo->env->time_to_sleep <= philo->env->time_to_die)
		ft_sleep(philo->env->time_to_sleep);
	else if (state == SLEEP
		&& philo->env->time_to_sleep > philo->env->time_to_die)
		ft_sleep(philo->env->time_to_die);
}
