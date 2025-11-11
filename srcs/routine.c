/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 21:15:26 by adias-do          #+#    #+#             */
/*   Updated: 2025/11/11 21:37:33 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
	{
		ft_usleep(1, philo);
	}
	while (!dead_loop(philo))
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

void	thinking(t_philo *philo)
{
	long long	think_t;

	print_state("is thinking", philo);
	if (philo->rules->number_of_philos % 2 != 0)
	{
		think_t = (philo->rules->time_to_eat * 2) - philo->rules->time_to_sleep;
		if (think_t < 0)
			think_t = 0;
		if (think_t > 0)
			ft_usleep(think_t, philo);
	}
}

void	sleeping(t_philo *philo)
{
	print_state("is sleeping", philo);
	ft_usleep(philo->rules->time_to_sleep, philo);
}

void	eating(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	if (philo->id % 2 == 0)
	{
		first = philo->l_fork;
		second = philo->r_fork;
	}
	else
	{
		first = philo->r_fork;
		second = philo->l_fork;
	}
	if (!grab_forks(philo, first, second))
		return ;
	print_state("is eating", philo);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	ft_usleep(philo->rules->time_to_eat, philo);
	pthread_mutex_unlock(first);
	pthread_mutex_unlock(second);
}

int	grab_forks(t_philo *phi, pthread_mutex_t *f, pthread_mutex_t *sec)
{
	pthread_mutex_lock(f);
	print_state("has taken a fork", phi);
	if (phi->rules->number_of_philos == 1)
	{
		usleep(phi->rules->time_to_die * 1010);
		pthread_mutex_unlock(f);
		return (0);
	}
	if (dead_loop(phi))
	{
		pthread_mutex_unlock(f);
		return (0);
	}
	pthread_mutex_lock(sec);
	print_state("has taken a fork", phi);
	return (1);
}
