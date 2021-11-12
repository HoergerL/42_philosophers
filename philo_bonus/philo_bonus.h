/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhoerger <lhoerger@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 17:45:22 by lhoerger          #+#    #+#             */
/*   Updated: 2021/11/12 08:31:28 by lhoerger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>

# define TAKE_FORK	0
# define EATING		1
# define SLEEPING	2
# define THINKING	3
# define DEAD		4

typedef struct s_data
{
	int				number_philo_total;
	int				number_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_meals;
	sem_t			*forks;
	sem_t			*sem_printf;
	unsigned long	start_time;
	unsigned long	start_time_first;
	unsigned long	total_time;
	unsigned long	last_eat;
	int				pid;

}					t_data;

//input_check
int		input_check(int argc, char *argv[], t_data *data);
void	get_input(int argc, char *argv[], t_data *data);
size_t	ft_strlen(const char *s);
int		ft_isdigit(int c);
void	ft_putnbr(int n);

//libft_utils
int		ft_atoi(const char *str);
void	ft_bzero(void *s, size_t n);

//regulate_time
void	ft_usleep(int time_to_sleep);
void	calculate_start_time(t_data *data_philo);

//killer
void	*check_philo(void *arg);
void	create_killer(t_data *data);

//print
void	protected_printf(t_data *phi, int mode);

//daily work
void	philo_eat(t_data *data);
void	philo_sleep(t_data *data);
void	philo_think(t_data *data);
int		catch_one_philo(t_data *data_philo, int i);
void	daily_work(t_data *data);
#endif