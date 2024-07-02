/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hai <hai@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:38:31 by hai               #+#    #+#             */
/*   Updated: 2024/07/01 10:39:18 by hai              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	end_check(t_table *table, int i)
{
	pthread_mutex_lock(&table->philosopher[i].philo_mutex);
	if (((get_time_mircoseconds()
				- table->philosopher[i].last_meal_time) >= table->time_to_die)
		&& !table->philosopher[i].eating)
	{
		write_status(DIED, table->philosopher + i);
		pthread_mutex_lock(&table->table_mutex);
		table->end_simulation = true;
		pthread_mutex_unlock(&table->table_mutex);
	}
	if (table->philosopher[i].eat_times == table->meals_limit
		&& !table->philosopher[i].counted)
	{
		table->philosopher[i].counted = true;
		pthread_mutex_lock(&table->table_mutex);
		table->finished++;
		pthread_mutex_unlock(&table->table_mutex);
	}
	pthread_mutex_unlock(&table->philosopher[i].philo_mutex);
}

void	*monitor(void *data)
{
	t_table	*table;
	int		i;

	table = (t_table *)data;
	while (!all_threads_running(table))
		;
	while (!end_process(table))
	{
		i = -1;
		while (++i < table->philo_number)
		{
			end_check(table, i);
			pthread_mutex_lock(&table->table_mutex);
			if (table->finished == table->philo_number)
				table->end_simulation = true;
			pthread_mutex_unlock(&table->table_mutex);
		}
	}
	return (NULL);
}
