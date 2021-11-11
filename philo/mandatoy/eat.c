/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhoerger <lhoerger@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 16:23:18 by lhoerger          #+#    #+#             */
/*   Updated: 2021/11/10 14:40:49 by lhoerger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	grep_fork(int side, t_data *data_philo)
{
	if (side == LEFT)
		pthread_mutex_lock(data_philo->fork_left);
	else
		pthread_mutex_lock(data_philo->fork_right);
	protected_printf(data_philo, TAKE_FORK);
}

void	eat(t_data *data_philo)
{
	calculate_start_time_i(data_philo);
	data_philo->last_eat = data_philo->start_time;
	protected_printf(data_philo, EATING);
	sleep_thread(data_philo->time_to_eat, data_philo);
}

void	philo_eat(t_data *data_philo)
{
	if (data_philo->number_philo % 2 == 1)
	{
		grep_fork(LEFT, data_philo);
		grep_fork(RIGHT, data_philo);
		eat(data_philo);
		pthread_mutex_unlock(data_philo->fork_right);
		pthread_mutex_unlock(data_philo->fork_left);
	}
	else
	{
		grep_fork(RIGHT, data_philo);
		grep_fork(LEFT, data_philo);
		eat(data_philo);
		pthread_mutex_unlock(data_philo->fork_left);
		pthread_mutex_unlock(data_philo->fork_right);
	}
}
