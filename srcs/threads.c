/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 21:33:27 by adias-do          #+#    #+#             */
/*   Updated: 2025/11/09 21:36:42 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int		dead_loop(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->death_mutex);
	if (philo->rules->philo_died == true)
		return (pthread_mutex_unlock(&philo->rules->death_mutex), 1);
	pthread_mutex_unlock(&philo->rules->death_mutex);
	return (0);
}

void	*monitor(void *arg)
{
	int			i;
	t_philo		*philo;
	long long	last;
	
	philo = (t_philo *)arg;
	while (1)
	{
		i = 0;
		while (i < philo[0].rules->number_of_philos)
		{
			pthread_mutex_lock(&philo[i].meal_mutex);
			last = philo[i].last_meal;
			pthread_mutex_unlock(&philo[i].meal_mutex);
			if ((get_time() - last) > philo[i].rules->time_to_die)
			{
				print_state("has died", &philo[i]);
				pthread_mutex_lock(&philo[i].rules->death_mutex);
				philo[i].rules->philo_died = true;
				pthread_mutex_unlock(&philo[i].rules->death_mutex);
				return (NULL);
			}
			i++;
		}
		if (!check_if_all_ate(philo))
		{
			pthread_mutex_lock(&philo[0].rules->death_mutex);
			philo[0].rules->philo_died = true;
			pthread_mutex_unlock(&philo[0].rules->death_mutex);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}

void	create_threads(t_philo *philo, t_rules *rules)
{
	int			i;
	pthread_t	monitor_thread;

	if (pthread_create(&monitor_thread, NULL, &monitor, philo) != 0)
		return ; // funcao pra destruir, limpar e sair.
	i = 0;
	while (i < rules->number_of_philos)
	{
		if (pthread_create(&philo[i].thread, NULL, &philo_routine, &philo[i]) != 0)
			return ; // funcao pra destruir, limpar e sair.
		i++;
	}
	i = 0;
	if (pthread_join(monitor_thread, NULL) != 0)
		return ; // funcao pra destruir, limpar e sair.
	while (i < rules->number_of_philos)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
			return ; // funcao pra destruir, limpar e sair.
		i++;
	}
}
