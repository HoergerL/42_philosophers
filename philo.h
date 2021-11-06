/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhoerger <lhoerger@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 17:45:22 by lhoerger          #+#    #+#             */
/*   Updated: 2021/11/06 15:49:27 by lhoerger         ###   ########.fr       */
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

#endif