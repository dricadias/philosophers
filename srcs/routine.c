/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 21:15:26 by adias-do          #+#    #+#             */
/*   Updated: 2025/11/10 14:25:37 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	
	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
	{
		thinking(philo);
		usleep(philo->rules->time_to_eat * 500);
	}
	while(!dead_loop(philo))
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

void	thinking(t_philo *philo)
{
	print_state("is thinking", philo);
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
	pthread_mutex_lock(first);
	print_state("has taken a fork", philo);
	if (philo->rules->number_of_philos == 1)
	{
		usleep(philo->rules->time_to_die * 1000);
		pthread_mutex_unlock(first);
		return ;
	}
	if (dead_loop(philo))
	{
		pthread_mutex_unlock(first);
		return ;
	}
	pthread_mutex_lock(second);
	print_state("has taken a fork", philo);
	print_state("is eating", philo);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	ft_usleep(philo->rules->time_to_eat, philo);
	pthread_mutex_unlock(first);
	pthread_mutex_unlock(second);
}

