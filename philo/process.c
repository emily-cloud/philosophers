/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hai <hai@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:26:56 by hai               #+#    #+#             */
/*   Updated: 2024/07/01 11:02:19 by hai              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *data)
{
	t_table	*table;
	t_philo	*philosopher;

	philosopher = (t_philo *)data;
	table = philosopher->table;
	wait_ready(philosopher->table);
	pthread_mutex_lock(&table->table_mutex);
	table->running_thread++;
	pthread_mutex_unlock(&table->table_mutex);
	pthread_mutex_lock(&philosopher->philo_mutex);
	philosopher->last_meal_time = get_time_mircoseconds();
	pthread_mutex_unlock(&philosopher->philo_mutex);
	dinner_plan(philosopher);
	while (!end_process(table))
	{
		eat_action(philosopher);
		write_status(SLEEPING, philosopher);
		ft_usleep(table->sleep_time);
		thinking(philosopher, false);
	}
	return (NULL);
}

void	*one_routine(void *data)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)data;
	table = philo->table;
	table->start_time = get_time_mircoseconds();
	philo->last_meal_time = get_time_mircoseconds();
	write_status(TAKE_FIRST_FORK, philo);
	if ((get_time_mircoseconds() - philo->last_meal_time) < table->time_to_die)
		ft_usleep(table->time_to_die - (get_time_mircoseconds()
				- philo->last_meal_time));
	write_status(DIED, philo);
	return (NULL);
}

int	case_one(t_table *table)
{
	if (pthread_create(&table->philosopher->philo_thread, NULL, &one_routine,
			table->philosopher) != 0)
		return (error_print(PHILO_CREATE_FAILED, table));
	pthread_join(table->philosopher->philo_thread, NULL);
	return (0);
}

int	start_process(t_table *table)
{
	int	i;

	i = -1;
	if (table->meals_limit == 0 || table->philo_number == 0)
		return (0);
	if (table->philo_number == 1)
		return (case_one(table));
	while (++i < table->philo_number)
	{
		if (pthread_create(&table->philosopher[i].philo_thread, NULL, &routine,
				&table->philosopher[i]) != 0)
			return (error_print(PHILO_CREATE_FAILED, table));
	}
	if (pthread_create(&table->monitor, NULL, &monitor, table) != 0)
		return (error_print(MINOTOR_CFAILED, table));
	pthread_mutex_lock(&table->table_mutex);
	table->ready_to_start = true;
	table->start_time = get_time_mircoseconds();
	pthread_mutex_unlock(&table->table_mutex);
	join_philosphers(table);
	pthread_join(table->monitor, NULL);
	return (0);
}
