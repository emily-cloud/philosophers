/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hai <hai@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:36:12 by hai               #+#    #+#             */
/*   Updated: 2024/07/01 11:00:03 by hai              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	read_bool(pthread_mutex_t *mutex, bool *value)
{
	bool	result;

	pthread_mutex_lock(mutex);
	result = *value;
	pthread_mutex_unlock(mutex);
	return (result);
}

bool	end_process(t_table *table)
{
	bool	result;

	pthread_mutex_lock(&table->table_mutex);
	result = table->end_simulation;
	pthread_mutex_unlock(&table->table_mutex);
	return (result);
}

void	wait_ready(t_table *table)
{
	while (!read_bool(&table->table_mutex, &table->ready_to_start))
		ft_usleep(1000);
}

void	dinner_plan(t_philo *philo)
{
	if (philo->table->philo_number % 2 == 0)
	{
		if (philo->id % 2 == 0)
			ft_usleep(30000);
	}
	else
	{
		if (philo->id % 2)
			thinking(philo, true);
	}
}

void	write_status(t_symbol symble, t_philo *philo)
{
	long	elapsed;

	if (end_process(philo->table))
		return ;
	elapsed = (long)(get_time_mircoseconds() - philo->table->start_time) / 1000;
	pthread_mutex_lock(&philo->table->write_mutex);
	if (symble == DIED)
		printf(R"%ld %d is dead\n"B, elapsed, philo->id);
	if (symble == TAKE_FIRST_FORK && !end_process(philo->table))
		printf("%ld %d has taken a fork\n", elapsed, philo->id);
	if (symble == TAKE_SECOND_FORK && !end_process(philo->table))
		printf("%ld %d has taken a fork\n", elapsed, philo->id);
	if (symble == EATING && !end_process(philo->table))
		printf(G "%ld %d is eating\n" B, elapsed, philo->id);
	if (symble == SLEEPING && !end_process(philo->table))
		printf("%ld %d is sleeping\n", elapsed, philo->id);
	if (symble == THINKING && !end_process(philo->table))
		printf("%ld %d is thinking\n", elapsed, philo->id);
	pthread_mutex_unlock(&philo->table->write_mutex);
}
