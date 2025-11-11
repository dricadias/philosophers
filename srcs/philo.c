/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 01:01:01 by adias-do          #+#    #+#             */
/*   Updated: 2025/11/11 15:00:19 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int argc, char **argv)
{
	t_rules		rules;
	t_philo		*philo;

	if (argc < 5 || argc > 6 || check_args(argv))
		return (printf("error: invalid args.\n"), 1);
	if (init_rules(&rules, argv) != 0)
		destroy_all(NULL, &rules);
	rules.start_time = get_time();
	philo = init_philos(&rules);
	if (!philo)
		destroy_all(philo, &rules);
	create_threads(philo, &rules);
	destroy_all(philo, &rules);
	return (0);
}
