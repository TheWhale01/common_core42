/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 16:41:30 by hubretec          #+#    #+#             */
/*   Updated: 2022/04/29 17:40:30 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_philo	*philos;

	if (!check(ac, av))
	{
		printf("Error\n");
		return (0);
	}
	philos = init(ac, av);
	launch(philos);
	free_philos(philos);
	return (0);
}
