/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hai <hai@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:33:06 by hai               #+#    #+#             */
/*   Updated: 2024/07/01 10:33:16 by hai              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc == 5 || argc == 6)
	{
		if (valid_check(argv))
			return (1);
		if (parse_input(&table, argv))
			return (1);
		if (start_process(&table))
			return (1);
		exit_clean(&table);
		return (0);
	}
	else
		return (error_print(INVALID_INPUT, NULL));
}
