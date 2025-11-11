/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 14:06:54 by adias-do          #+#    #+#             */
/*   Updated: 2025/11/11 11:38:05 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	init_mutexes(t_rules *rules)
{
	int	i;

	i = 0;
	rules->forks = malloc(sizeof(pthread_mutex_t) * rules->number_of_philos);
	if (!rules->forks)
		return (1);
	while (i < rules->number_of_philos)
	{
		if (pthread_mutex_init(&rules->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_mutex_init(&rules->print_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&rules->death_mutex, NULL) != 0)
		return (1);
	return (0);
}

int	init_rules(t_rules *rules, char **argv)
{
	rules->number_of_philos = ft_atol(argv[1]);
	rules->time_to_die = ft_atol(argv[2]);
	rules->time_to_eat = ft_atol(argv[3]);
	rules->time_to_sleep = ft_atol(argv[4]);
	rules->must_eat = -1;
	rules->has_limit = false;
	rules->philo_died = false;
	if (argv[5])
	{
		rules->must_eat = ft_atol(argv[5]);
		rules->has_limit = true;
	}
	if (init_mutexes(rules))
		return (1);
	return (0);
}

t_philo	*init_philos(t_rules *rules)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = malloc(sizeof(t_philo) * rules->number_of_philos);
	if (!philos)
		return (NULL);
	while (i < rules->number_of_philos)
	{
		philos[i].id = i + 1;
		philos[i].meals_eaten = 0;
		philos[i].last_meal = rules->start_time;
		philos[i].l_fork = &rules->forks[i];
		philos[i].r_fork = &rules->forks[(i + 1) % rules->number_of_philos];
		philos[i].rules = rules;
		if (pthread_mutex_init(&philos[i].meal_mutex, NULL) != 0)
			return (NULL);
		i++;
	}
	return (philos);
}
