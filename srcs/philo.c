/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 01:01:01 by adias-do          #+#    #+#             */
/*   Updated: 2025/11/10 18:24:56 by adias-do         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_rules		rules;
	t_philo		*philo;

	if (argc < 5 || argc > 6 || check_args(argv))
		return (printf("error: invalid args.\n"), 1);
	if (init_rules(&rules, argv) != 0)
		destroy_all(NULL, &rules);
	philo = init_philos(&rules);
	if (!philo)
		destroy_all(philo, &rules);
	rules.start_time = get_time();
	create_threads(philo, &rules);
	destroy_all(philo, &rules);
	return (0);
}
