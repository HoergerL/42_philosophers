/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhoerger <lhoerger@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 11:00:20 by lhoerger          #+#    #+#             */
/*   Updated: 2021/11/07 13:06:16 by lhoerger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_data(t_data *data)
{
	printf("data:\nnumber_philo : %i\n"
	"number_philo_total : %i\n"
	"time_to_die: %i\n"
	"time_to_eat: %i\n"
	"time_to_sleep: %i\n"
	"number meals: %i\n\n\n", 
	data->number_philo, 
	data->number_philo_total, 
	data->time_to_die, 
	data->time_to_eat, 
	data->time_to_sleep, 
	data->number_meals);
}

void protected_printf(t_data *data_philo, int mode)
{
	static int print = 1;
	//printf("dead%i nr %i\n", data_philo->dead, data_philo->number_philo);
	
	pthread_mutex_lock(data_philo->mutex_print);
	if (data_philo->dead != 0 || print != 1)
	{
		pthread_mutex_unlock(data_philo->mutex_print);
		return ;
	}
	calculate_start_time(data_philo);
	if (mode == TAKE_FORK)
		printf("%-10lu %i has taken a fork\n", data_philo->total_time, data_philo->number_philo);
	else if (mode == EATING)
		printf("%-10lu %i is eating\n", data_philo->total_time, data_philo->number_philo);
	else if (mode == SLEEPING)
		printf("%-10lu %i is sleeping\n", data_philo->total_time, data_philo->number_philo);
	else if (mode == THINKING)
		printf("%-10lu %i is thinking\n", data_philo->total_time, data_philo->number_philo);
	else if (mode == DEAD)
	{
		printf("%-10lu %i died\n", data_philo->total_time, data_philo->number_philo);
		print = 0;
	}
	pthread_mutex_unlock(data_philo->mutex_print);
}