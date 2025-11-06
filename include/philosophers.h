/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 19:28:42 by adias-do          #+#    #+#             */
/*   Updated: 2025/11/06 14:09:38 by adias-do         ###   ########.fr       */
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

typedef enum	e_state
{
	THINKING,
	EATING,
	SLEEPING,
	DIED,
	TOOK_FORK
}	t_state;

// tudo que for compartilhado entre eles
typedef struct	s_rules
{
	int				number_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	bool			has_limit;
	bool			philo_died;
	long long		start_time; // calcular os timestamps (tempo_atual - start_time)
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
}	t_rules;

// cada philo
typedef struct	s_philo
{
	int				id;
	int				status;
	int				meals_eaten;
	long long		last_meal;
	pthread_t		thread;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	t_rules			*rules;
}	t_philo;



// utils
int			check_args(char **argv);
long		ft_atol(const char *str);
long long	get_time(void);


// init structs
int			init_rules(t_rules *rules, char **argv);
t_philo		*init_philos(t_rules *rules);


#endif