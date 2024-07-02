/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hai <hai@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:32:38 by hai               #+#    #+#             */
/*   Updated: 2024/07/01 10:38:08 by hai              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	read_long(long time, t_philo *philo)
{
	long	result;

	pthread_mutex_lock(&philo->table->table_mutex);
	result = time;
	pthread_mutex_unlock(&philo->table->table_mutex);
	return (result);
}

void	eat_action(t_philo *philo)
{
	pthread_mutex_lock(&philo->first_fork->fork_mutex);
	write_status(TAKE_FIRST_FORK, philo);
	pthread_mutex_lock(&philo->second_fork->fork_mutex);
	write_status(TAKE_SECOND_FORK, philo);
	write_status(EATING, philo);
	pthread_mutex_lock(&philo->philo_mutex);
	philo->eating = true;
	philo->last_meal_time = get_time_mircoseconds();
	philo->eat_times += 1;
	pthread_mutex_unlock(&philo->philo_mutex);
	ft_usleep(philo->table->eat_time);
	pthread_mutex_unlock(&philo->first_fork->fork_mutex);
	pthread_mutex_unlock(&philo->second_fork->fork_mutex);
	pthread_mutex_lock(&philo->philo_mutex);
	philo->eating = false;
	pthread_mutex_unlock(&philo->philo_mutex);
}

void	thinking(t_philo *philo, bool pre_process)
{
	long	t_wait;
	long	t_sleep;
	long	t_eat;

	if (!pre_process)
		write_status(THINKING, philo);
	if (philo->table->philo_number % 2 == 0)
		return ;
	t_sleep = philo->table->sleep_time;
	t_eat = philo->table->eat_time;
	t_wait = (t_eat * 2) - t_sleep;
	if (t_wait < 0)
		t_wait = 0;
	ft_usleep(t_wait * 0.4);
}
