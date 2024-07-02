/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hai <hai@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:30:19 by hai               #+#    #+#             */
/*   Updated: 2024/07/01 10:58:52 by hai              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(const char *str)
{
	long	number;
	int		i;
	int		sign;

	i = 0;
	sign = 1;
	number = 0;
	while ((str[i] <= 13 && str[i] >= 9) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		number *= 10;
		number += str[i] - '0';
		i++;
	}
	return (number * sign);
}

void	free_all(t_table *table)
{
	if (table->fork)
		free(table->fork);
	if (table->philosopher)
		free(table->philosopher);
}

int	error_print(char *str, t_table *table)
{
	printf("%s\n", str);
	if (table)
	{
		printf("erro_print 65/n");
		exit_clean(table);
	}
	return (1);
}

void	exit_clean(t_table *table)
{
	int	i;

	i = -1;
	if (table->fork)
	{
		while (++i < table->philo_number)
			pthread_mutex_destroy(&table->fork[i].fork_mutex);
	}
	i = -1;
	if (table->philosopher)
	{
		while (++i < table->philo_number)
		{
			pthread_mutex_destroy(&table->philosopher[i].philo_mutex);
		}
	}
	pthread_mutex_destroy(&table->write_mutex);
	pthread_mutex_destroy(&table->table_mutex);
	free_all(table);
}

void	join_philosphers(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_number)
		pthread_join(table->philosopher[i].philo_thread, NULL);
}
