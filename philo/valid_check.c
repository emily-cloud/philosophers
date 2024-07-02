/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hai <hai@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:35:43 by hai               #+#    #+#             */
/*   Updated: 2024/07/01 11:00:07 by hai              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_digit(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			while ((argv[i][j] >= 9 && argv[i][j] <= 13) || argv[i][j] == 32)
				j++;
			if (argv[i][j] == '-')
				return (error_print(INPUT_NEGETIVE, NULL));
			if (!(argv[i][j] >= 48 && argv[i][j] <= 57))
				return (error_print(INPUT_UNDIGIT, NULL));
			j++;
		}
		i++;
	}
	return (0);
}

int	count_digit(char *argv)
{
	int	i;
	int	d_count;

	i = 0;
	d_count = 0;
	while (argv[i] && (!(argv[i] >= 48 && argv[i] <= 57)))
		i++;
	while (argv[i] >= 48 && argv[i] <= 57)
	{
		d_count++;
		i++;
	}
	return (d_count);
}

int	check_length(char **argv)
{
	int	i;
	int	d_count;

	i = 1;
	while (argv[i])
	{
		d_count = count_digit(argv[i]);
		if (d_count > 10)
			return (error_print(INPUT_TOOLONG, NULL));
		i++;
	}
	return (0);
}

int	check_limit(char **argv)
{
	int	i;

	i = 1;
	while (++i < 5)
	{
		if (ft_atol(argv[i]) > INT_MAX || ft_atol(argv[i]) < INT_MIN)
			return (error_print(INPUT_EXCEEDLIMIT, NULL));
		if (ft_atol(argv[i]) < 60)
			return (error_print(INPUT_TOO_SMALL, NULL));
	}
	if (ft_atol(argv[1]) > 200)
		return (error_print(PHILO_EXCEED, NULL));
	return (0);
}

int	valid_check(char **argv)
{
	if (check_digit(argv))
		return (1);
	if (check_length(argv))
		return (1);
	if (check_limit(argv))
		return (1);
	return (0);
}
