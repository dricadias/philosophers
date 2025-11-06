/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 01:01:01 by adias-do          #+#    #+#             */
/*   Updated: 2025/11/06 14:07:34 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int argc, char **argv)
{
	t_rules	rules;
	t_philo	*philos;

	(void)argv;
	if (argc < 5 || argc > 6 || check_args(argv))
		return (printf("error: invalid args.\n"), 1);
	if (init_rules(&rules, argv) != 0)
		// funcao de limpar tudo e sair !
	philos = init_philos(&rules);
	if (!philos)
		// funcao de limpar tudo e sair !
	
	// funcao de limpar tudo e sair !
	return (0);
}























/* 	rules.number_of_philos = atoi(argv[1]);
	rules.time_to_die = atoi(argv[2]);
	rules.time_to_eat = atoi(argv[3]);
	rules.time_to_sleep = atoi(argv[4]);
	if (argc == 6)
	{
		rules.must_eat = atoi(argv[5]);
		rules.has_limit = true;
	}
	else
	{
		rules.must_eat = -1;
		rules.has_limit = false;
	}
	if (rules.number_of_philos <= 0 || rules.time_to_die <= 0 || rules.time_to_eat <= 0 || rules.time_to_sleep <= 0 || rules.must_eat <= 0)
		return(printf("error: invalid values\n"), 1);
	return (0); */
















// testes

/* void	init_rules(t_rules *rules, int num_philos)
{
	int	i;

	i = 0;
	rules->num_philos = num_philos;
	rules->forks = malloc(sizeof(pthread_mutex_t) * num_philos);
	if (!rules->forks)
		return ; // tratar o erro
	while (i < num_philos)
	{
		pthread_mutex_init(&rules->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&rules->print_mutex, NULL);
}

void	*philosopher(void *arg)
{
	t_philos *philo = (t_philos *)arg;
	
	pthread_mutex_lock(&philo->rules->print_mutex);
	printf("filosofo %d começou a pensar\n", philo->id);
	pthread_mutex_unlock(&philo->rules->print_mutex);
	
	usleep(50000);
	
	pthread_mutex_lock(&philo->rules->print_mutex);
	printf("filosofo %d terminou de pensar\n", philo->id);
	pthread_mutex_unlock(&philo->rules->print_mutex);
	
	return (NULL);
} */