/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 16:39:37 by hubretec          #+#    #+#             */
/*   Updated: 2022/04/29 16:39:37 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_env	*init_env(int ac, char **av)
{
	int		i;
	t_env	*env;

	i = -1;
	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->nb_philos = ft_atoll(av[1]);
	env->forks = malloc(sizeof(pthread_mutex_t) * env->nb_philos);
	if (!env->forks)
		return (NULL);
	env->died = 0;
	env->start_time = get_ms();
	env->limit_eat = -1;
	if (ac == 6)
		env->limit_eat = ft_atoll(av[5]);
	env->time_to_die = ft_atoll(av[2]);
	env->time_to_eat = ft_atoll(av[3]);
	env->time_to_sleep = ft_atoll(av[4]);
	pthread_mutex_init(&(env->death), NULL);
	pthread_mutex_init(&(env->write), NULL);
	while (++i < env->nb_philos)
		pthread_mutex_init(&env->forks[i], NULL);
	return (env);
}

t_philo	*init(int ac, char **av)
{
	int		i;
	t_env	*env;
	t_philo	*philos;

	i = -1;
	env = init_env(ac, av);
	philos = malloc(sizeof(t_philo) * env->nb_philos);
	if (!philos)
		return (NULL);
	while (++i < env->nb_philos)
	{
		philos[i].id = i;
		philos[i].nb_eaten = 0;
		philos[i].last_meal = 0;
		philos[i].env = env;
	}
	return (philos);
}
