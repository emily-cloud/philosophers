/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hai <hai@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:29:42 by hai               #+#    #+#             */
/*   Updated: 2024/07/01 11:37:54 by hai              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define MALLOC_TFAILED "Table malloc failed"
# define MALLOC_PHILO "philosopher malloc failed"
# define MALLOC_FORK "fork malloc failed"
# define INVALID_INPUT "Inpout is invalid"
# define INPUT_NEGETIVE "Input can not be negetive number"
# define INPUT_UNDIGIT "Input is not digit"
# define INPUT_TOOLONG "Input number exceed INTMAX"
# define INPUT_EXCEEDLIMIT "Input is exceed integer limits"
# define PHILO_EXCEED "philosopher number is more than 200"
# define TMUTEX_FAILED "Table mutex initialision failed"
# define WMUTEX_FALIED "write mutex initialision failed"
# define MINOTOR_CFAILED "Moniter create failed"
# define FORK_INIT_FALIED "Fork mutex initialision failed"
# define PHILO_CREATE_FAILED "Philosphe thread initialize failed"
# define SUPERVISER_FAILED "Superviser init failed"
# define PMUTEX_FALIED "Philo mutex init failed"
# define INPUT_TOO_SMALL "Time can not be smaller than 60ms"

# define G "\033[1;32m"
# define R "\033[1;31m"
# define B "\033[0m"

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_table	t_table;

typedef struct s_fork
{
	int					fork_id;
	pthread_mutex_t		fork_mutex;
}						t_fork;
typedef struct s_philo
{
	int					id;
	int					eat_times;
	bool				eating;
	bool				counted;
	long				last_meal_time;
	pthread_t			philo_thread;
	pthread_mutex_t		philo_mutex;
	t_fork				*first_fork;
	t_fork				*second_fork;
	t_table				*table;
}						t_philo;

typedef struct s_table
{
	int					philo_number;
	int					running_thread;
	long				time_to_die;
	long				eat_time;
	long				sleep_time;
	int					meals_limit;
	int					finished;
	long				start_time;
	bool				ready_to_start;
	bool				end_simulation;
	pthread_mutex_t		table_mutex;
	pthread_mutex_t		write_mutex;
	pthread_t			monitor;
	t_fork				*fork;
	t_philo				*philosopher;
}						t_table;

typedef enum e_symbol
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}						t_symbol;

int						parse_input(t_table *table, char **argv);
int						malloc_table(t_table *table);
int						init_table(t_table *table);
int						init_forks(int i, t_table *table, t_fork *fork);
int						init_philo_thread(int i, t_table *table,
							t_philo *philo);

void					wait_ready(t_table *table);
bool					all_threads_running(t_table *table);
void					dinner_plan(t_philo *philo);
void					write_status(t_symbol symble, t_philo *philo);
bool					read_bool(pthread_mutex_t *mutex, bool *value);

void					eat_action(t_philo *philo);
void					thinking(t_philo *philo, bool pre_process);

int						start_process(t_table *table);
void					*one_routine(void *data);
int						case_one(t_table *table);
void					*routine(void *table);
void					*monitor(void *table);
bool					end_process(t_table *table);

long					ft_atol(const char *str);
long					get_time_mircoseconds(void);
void					free_all(t_table *table);
int						error_print(char *str, t_table *table);
void					exit_clean(t_table *table);
void					join_philosphers(t_table *table);
void					ft_usleep(long time);

int						check_digit(char **argv);
int						count_digit(char *argv);
int						check_length(char **argv);
int						check_limit(char **argv);
int						valid_check(char **argv);

#endif
