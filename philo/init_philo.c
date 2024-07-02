/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hai <hai@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:50:44 by hai               #+#    #+#             */
/*   Updated: 2024/07/01 10:54:33 by hai              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_forks(t_philo *philo, t_fork *forks, int philo_position)
{
	int	philo_nbr;

	philo_nbr = philo->table->philo_number;
	if (philo->id % 2)
	{
		philo->first_fork = &forks[((philo_position + 1) % philo_nbr)];
		philo->second_fork = &forks[philo_position];
	}
	else
	{
		philo->first_fork = &forks[philo_position];
		philo->second_fork = &forks[(philo_position + 1) % philo_nbr];
	}
}

int	init_philo_thread(int i, t_table *table, t_philo *philo)
{
	philo->id = i + 1;
	philo->eat_times = 0;
	philo->last_meal_time = 0;
	philo->table = table;
	philo->eating = false;
	philo->counted = false;
	if (pthread_mutex_init(&philo->philo_mutex, NULL) != 0)
		return (error_print(PMUTEX_FALIED, table));
	assign_forks(philo, table->fork, i);
	return (0);
}

int	init_table(t_table *table)
{
	int	i;

	if (malloc_table(table))
		return (1);
	i = -1;
	while (++i < table->philo_number)
	{
		if (init_forks(i, table, &table->fork[i]))
			return (1);
	}
	i = -1;
	while (++i < table->philo_number)
	{
		if (init_philo_thread(i, table, &table->philosopher[i]))
			return (1);
	}
	return (0);
}
