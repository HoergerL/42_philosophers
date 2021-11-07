/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhoerger <lhoerger@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 17:45:22 by lhoerger          #+#    #+#             */
/*   Updated: 2021/11/07 13:07:08 by lhoerger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>

# define TAKE_FORK	0
# define EATING		1
# define SLEEPING	2
# define THINKING	3
# define DEAD		4



typedef struct s_data
{
	int number_philo_total;
	int number_philo;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int number_meals;
	int dead;
	int finished;
	struct timeval start_tv;
	struct timeval end_tv;
	unsigned long start_time;
	unsigned long end_time;
	unsigned long total_time;
	unsigned long start_time_first;
	unsigned long last_eat;
	
	
	pthread_mutex_t *fork_left;
	pthread_mutex_t *fork_right;
	pthread_mutex_t **total_mutexes;
	pthread_mutex_t *mutex_print;
}					t_data;

//input_check
int	input_check(int argc, char *argv[], t_data *data);
void	get_input(int argc, char *argv[], t_data *data);
int	ft_atoi(const char *str);
size_t	ft_strlen(const char *s);
int	ft_isdigit(int c);
void	ft_putnbr(int n);

//prints
void	print_data(t_data *data);
void protected_printf(t_data *data_philo, int mode);

//create_threads.c
t_data	*copy_global_data(t_data *global_data, int i);
void	init_mutexes(t_data *data);
int	create_philos(t_data *global_data);


void	calculate_start_time(t_data *data_philo);
void	*philo_daily_work(void *arg);
void	*stalk_philos(void *arg);
#endif