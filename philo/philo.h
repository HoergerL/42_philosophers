/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhoerger <lhoerger@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 17:45:22 by lhoerger          #+#    #+#             */
/*   Updated: 2021/11/12 15:11:34 by lhoerger         ###   ########.fr       */
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

# define LEFT		1
# define RIGHT		2

typedef struct s_data
{
	int				number_philo_total;
	int				number_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_meals;
	int				dead;
	int				finished;
	struct timeval	start_tv;
	struct timeval	end_tv;
	unsigned long	start_time;
	unsigned long	end_time;
	unsigned long	total_time;
	unsigned long	start_time_first;
	unsigned long	last_eat;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	pthread_mutex_t	**total_mutexes;
	pthread_mutex_t	*mutex_print;
	pthread_mutex_t	*cnt_mutex;
}					t_data;

//input_check
int		input_check(int argc, char *argv[], t_data *data);
void	get_input(int argc, char *argv[], t_data *data);
size_t	ft_strlen(const char *s);
int		ft_isdigit(int c);
void	ft_putnbr(int n);

//prints
void	print_data(t_data *data);
void	protected_printf(t_data *data_philo, int mode);

//create_threads.c
t_data	*copy_global_data(t_data *global_data, int i);
int		init_mutexes(t_data *data);
int		create_philos(t_data *global_data);

//eat
void	grep_fork(int side, t_data *data_philo);
void	eat(t_data *data_philo);
void	philo_eat(t_data *data_philo);

//daily work
void	philo_sleep(t_data *data_philo);
void	philo_think(t_data *data_philo);
void	wait_for_others(t_data *data_philo);
void	*philo_daily_work(void *arg);
int		catch_one_philo(t_data *data_philo, int i);

//daily_work_utils
void	coordinate_philos(t_data *data_philo, int *i);
int		make_philos_ready(t_data *data_philo, int i);

//regulate time
int		counter_start(t_data *data);
void	sleep_thread(int time_to_sleep, t_data *data_philo);
void	calculate_start_time(t_data *data_philo);
int		get_start_time_first(t_data *data_philo, int stalker);
void	calculate_start_time_i(t_data *data_philo);

//free
void	free_mutexes(t_data *data);
void	free_data_philo(t_data *global_data, t_data **data);
void	free_data(t_data *global_data, t_data **data_philo, pthread_t *th);

void	calculate_start_time(t_data *data_philo);
void	*philo_daily_work(void *arg);
void	*stalk_philos(void *arg);
void	sleep_thread(int time_to_sleep, t_data *data_philo);
int		counter_start(t_data *data);
int		get_start_time_first(t_data *data_philo, int stalker);

//libft_utils
int		ft_atoi(const char *str);
void	ft_bzero(void *s, size_t n);
#endif