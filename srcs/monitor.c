/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 21:46:23 by adias-do          #+#    #+#             */
/*   Updated: 2025/11/11 21:32:41 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	check_if_all_ate(t_philo *philo)
{
	int	i;

	i = 0;
	if (!philo->rules->has_limit)
		return (1);
	while (i < philo[0].rules->number_of_philos)
	{
		pthread_mutex_lock(&philo[i].meal_mutex);
		if (philo[i].meals_eaten < philo->rules->must_eat)
		{
			pthread_mutex_unlock(&philo[i].meal_mutex);
			return (1);
		}
		pthread_mutex_unlock(&philo[i].meal_mutex);
		i++;
	}
	return (0);
}

int	check_dead(t_philo *philo)
{
	int			i;
	long long	last;
	long long	timestamp;

	i = 0;
	while (i < philo[0].rules->number_of_philos)
	{
		pthread_mutex_lock(&philo[i].meal_mutex);
		last = philo[i].last_meal;
		pthread_mutex_unlock(&philo[i].meal_mutex);
		if ((get_time() - last) > philo[i].rules->time_to_die)
		{
			pthread_mutex_lock(&philo->rules->print_mutex);
			pthread_mutex_lock(&philo[i].rules->death_mutex);
			philo[i].rules->philo_died = true;
			pthread_mutex_unlock(&philo[i].rules->death_mutex);
			timestamp = get_time() - philo[i].rules->start_time;
			printf("%lld %d %s\n", timestamp, philo[i].id, "has died");
			pthread_mutex_unlock(&philo->rules->print_mutex);
			return (1);
		}
		i++;
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (check_dead(philo))
			return (NULL);
		if (check_if_all_ate(philo) == 0)
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
