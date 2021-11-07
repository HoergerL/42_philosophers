/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regulate_time.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhoerger <lhoerger@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 16:41:42 by lhoerger          #+#    #+#             */
/*   Updated: 2021/11/07 18:29:12 by lhoerger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	counter_start(t_data *data)
{
	static int	cnt = 0;

	if (data->number_philo != 1)
	{
		pthread_mutex_lock(data->mutex_print);
		cnt++;
		pthread_mutex_unlock(data->mutex_print);
	}
	return (cnt);
}

void	sleep_thread(int time_to_sleep, t_data *data_philo)
{
	while (1)
	{
		usleep(100);
		gettimeofday(&data_philo->end_tv, NULL);
		data_philo->end_time = data_philo->end_tv.tv_sec * 1000
			+ data_philo->end_tv.tv_usec / 1000;
		if (data_philo->end_time - data_philo->start_time
			>= (unsigned long) time_to_sleep)
			break ;
	}
	data_philo->total_time = data_philo->total_time + data_philo->end_time
		- data_philo->start_time;
}

void	calculate_start_time(t_data *data_philo)
{
	gettimeofday(&data_philo->start_tv, NULL);
	data_philo->start_time = data_philo->start_tv.tv_sec * 1000
		+ data_philo->start_tv.tv_usec / 1000;
	data_philo->total_time = data_philo->start_time
		- data_philo->start_time_first;
}

int	get_start_time_first(t_data *data_philo, int stalker)
{
	static unsigned long	start_time_first = 0;
	struct timeval			start_tv;
	static int				cnt = 0;

	if (start_time_first == 0 && data_philo->number_philo == 1)
	{
		gettimeofday(&start_tv, NULL);
		start_time_first = start_tv.tv_sec * 1000 + start_tv.tv_usec / 1000;
	}
	if (start_time_first != 0 && stalker != 1)
	{
		data_philo->last_eat = start_time_first;
		data_philo->start_time_first = start_time_first;
		pthread_mutex_lock(data_philo->mutex_print);
		cnt++;
		pthread_mutex_unlock(data_philo->mutex_print);
	}
	return (cnt);
}
