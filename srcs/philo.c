/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 01:01:01 by adias-do          #+#    #+#             */
/*   Updated: 2025/11/09 21:36:49 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

// ./philo 15 500 400 300

void	print_state(char *str, t_philo *philo)
{
	long long	timestamp;

	if (dead_loop(philo))
		return ;
	pthread_mutex_lock(&philo->rules->print_mutex);
	timestamp = get_time() - philo->rules->start_time;
	printf("%lld %d %s\n", timestamp, philo->id, str);
	pthread_mutex_unlock(&philo->rules->print_mutex);
}

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

int	main(int argc, char **argv)
{
	t_rules		rules;
	t_philo		*philo;

	if (argc < 5 || argc > 6 || check_args(argv))
		return (printf("error: invalid args.\n"), 1);
	if (init_rules(&rules, argv) != 0)
		return (1); // funcao de limpar tudo e sair !
	philo = init_philos(&rules);
	if (!philo)
		return (1); // funcao de limpar tudo e sair !
	rules.start_time = get_time();
	create_threads(philo, &rules);
	// funcao de limpar tudo e sair !
	return (0);
}



/* 
	if (rules.number_of_philos <= 0 || rules.time_to_die <= 0 || rules.time_to_eat <= 0 || rules.time_to_sleep <= 0 || rules.must_eat <= 0)
		return(printf("error: invalid values\n"), 1);
	return (0); */
