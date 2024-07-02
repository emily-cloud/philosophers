/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hai <hai@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:31:46 by hai               #+#    #+#             */
/*   Updated: 2024/07/01 10:54:28 by hai              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	malloc_table(t_table *table)
{
	table->philosopher = malloc(table->philo_number * sizeof(t_philo));
	if (!table->philosopher)
		return (error_print(MALLOC_PHILO, table));
	table->fork = malloc(table->philo_number * sizeof(t_fork));
	if (!table->fork)
		return (error_print(MALLOC_FORK, table));
	return (0);
}

int	init_forks(int i, t_table *table, t_fork *fork)
{
	fork->fork_id = i;
	if (pthread_mutex_init(&fork->fork_mutex, NULL) != 0)
		return (error_print(FORK_INIT_FALIED, table));
	return (0);
}

int	parse_input(t_table *table, char **argv)
{
	table->philo_number = (int)ft_atol(argv[1]);
	table->running_thread = 0;
	table->time_to_die = ft_atol(argv[2]) * 1e3;
	table->eat_time = ft_atol(argv[3]) * 1e3;
	table->sleep_time = ft_atol(argv[4]) * 1e3;
	if (argv[5])
		table->meals_limit = (int)ft_atol(argv[5]);
	else
		table->meals_limit = INT_MAX;
	table->start_time = 0;
	table->finished = 0;
	table->ready_to_start = false;
	table->end_simulation = false;
	if (pthread_mutex_init(&table->table_mutex, NULL) != 0)
		return (error_print(TMUTEX_FAILED, table));
	if (pthread_mutex_init(&table->write_mutex, NULL) != 0)
		return (error_print(WMUTEX_FALIED, table));
	if (init_table(table))
		return (1);
	return (0);
}
