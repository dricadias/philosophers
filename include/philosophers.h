/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 19:28:42 by adias-do          #+#    #+#             */
/*   Updated: 2025/11/11 01:20:23 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>

# define PHILOS_MAX 200

// all that is shared between them
typedef struct s_rules
{
	int				number_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	bool			has_limit;
	bool			philo_died;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
}	t_rules;

// each philo
typedef struct s_philo
{
	int				id;
	int				status;
	int				meals_eaten;
	long long		last_meal;
	pthread_t		thread;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	t_rules			*rules;
}	t_philo;

// utils
int			check_args(char **argv);
long		ft_atol(const char *str);
long long	get_time(void);
void		ft_usleep(long long time, t_philo *philo);
int			grab_forks(t_philo *phi, pthread_mutex_t *f, pthread_mutex_t *sec);

// free
void		destroy_all(t_philo *philo, t_rules *rules);

// init structs
int			init_rules(t_rules *rules, char **argv);
t_philo		*init_philos(t_rules *rules);

// threads
int			dead_loop(t_philo *philo);
void		create_threads(t_philo *philo, t_rules *rules);

// philos routine
void		thinking(t_philo *philo);
void		sleeping(t_philo *philo);
void		eating(t_philo *philo);
void		*philo_routine(void *arg);

// monitor
int			check_if_all_ate(t_philo *philo);
void		*monitor(void *arg);

// main
int			main(int argc, char **argv);
void		print_state(char *str, t_philo *philo);

#endif