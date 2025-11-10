/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 16:45:30 by adias-do          #+#    #+#             */
/*   Updated: 2025/11/10 17:36:45 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	destroy_all(t_philo *philo, t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->number_of_philos)
	{
		pthread_mutex_destroy(&rules->forks[i]);
		pthread_mutex_destroy(&philo[i].meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&rules->death_mutex);
	pthread_mutex_destroy(&rules->print_mutex);
	free(rules->forks);
	free(philo);
}
