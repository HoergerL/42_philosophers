/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regulate_time_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhoerger <lhoerger@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 08:20:43 by lhoerger          #+#    #+#             */
/*   Updated: 2021/11/12 08:21:45 by lhoerger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_usleep(int time_to_sleep)
{
	unsigned long	time;
	struct timeval	time_tv;
	unsigned long	start_time;

	gettimeofday(&time_tv, NULL);
	start_time = time_tv.tv_sec * 1000 + time_tv.tv_usec / 1000;
	while (1)
	{
		usleep(100);
		gettimeofday(&time_tv, NULL);
		time = time_tv.tv_sec * 1000 + time_tv.tv_usec / 1000;
		if (time - start_time >= (unsigned long) time_to_sleep)
			break ;
	}
}

void	calculate_start_time(t_data *data)
{
	struct timeval	time_tv;

	gettimeofday(&time_tv, NULL);
	data->start_time = time_tv.tv_sec * 1000 + time_tv.tv_usec / 1000;
	data->total_time = data->start_time - data->start_time_first;
}
