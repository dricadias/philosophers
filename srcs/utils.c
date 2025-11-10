/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 14:05:11 by adias-do          #+#    #+#             */
/*   Updated: 2025/11/10 14:24:00 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

long	ft_atol(const char *str)
{
	int		i;
	int		sign;
	long	res;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sign);
}

int	check_args(char **argv)
{
	int		i;
	int		j;
	long	temp;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] == '+')
				j++;
			if (argv[i][j] == '-')
				return (1);
			if (argv[i][j] && (argv[i][j] < '0' || argv[i][j] > '9'))
				return (1);
			j++;
		}
		temp = ft_atol(argv[i]);
		if (temp > INT_MAX || temp <= 0)
			return (1);
		i++;
	}
	return (0);
}

long long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		write(2, "error: gettimeofday()\n", 23);
		exit(1);
	}
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_usleep(long long time, t_philo *philo)
{
	long long	start;

	start = get_time();
	while (!dead_loop(philo))
	{
		if (get_time() - start >= time)
			break ;
		usleep(500);
	}
}
