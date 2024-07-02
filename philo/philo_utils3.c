/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hai <hai@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:57:26 by hai               #+#    #+#             */
/*   Updated: 2024/07/01 11:51:47 by hai              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(long time)
{
	long	left_time;
	long	start;

	start = get_time_mircoseconds();
	while ((get_time_mircoseconds() - start) < time)
	{
		left_time = time - (get_time_mircoseconds() - start);
		if (left_time > 1e4)
			usleep(left_time / 2);
		else
		{
			while ((get_time_mircoseconds() - start) < time)
				;
		}
	}
}

long	get_time_mircoseconds(void)
{
	struct timeval	tv;
	long			microseconds;

	if (gettimeofday(&tv, NULL))
		return (1);
	microseconds = (long)((tv.tv_sec) * 1e6 + (long)(tv.tv_usec));
	return (microseconds);
}

bool	all_threads_running(t_table *table)
{
	bool	result;

	result = false;
	pthread_mutex_lock(&table->table_mutex);
	if (table->running_thread == table->philo_number)
		result = true;
	pthread_mutex_unlock(&table->table_mutex);
	return (result);
}
