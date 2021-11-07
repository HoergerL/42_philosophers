/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daily_work.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhoerger <lhoerger@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 16:30:25 by lhoerger          #+#    #+#             */
/*   Updated: 2021/11/07 16:35:01 by lhoerger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_sleep(t_data *data_philo)
{
	protected_printf(data_philo, SLEEPING);
	sleep_thread(data_philo->time_to_sleep, data_philo);
}

void	philo_think(t_data *data_philo)
{
	protected_printf(data_philo, THINKING);
}

void	wait_for_others(t_data *data_philo)
{
	int	i;

	i = 1;
	counter_start(data_philo);
	if (data_philo->number_philo == 1)
	{
		while (1)
		{
			if (counter_start(data_philo) == data_philo->number_philo_total - 1)
				break ;
		}
	}
	while (data_philo->start_time_first == 0)
		get_start_time_first(data_philo, 0);
}

int	catch_one_philo(t_data *data_philo, int i)
{
	while (data_philo->number_philo_total == 1)
	{
		if (i == 1)
		{
			i++;
			protected_printf(data_philo, TAKE_FORK);
		}
		if (data_philo->dead != 0)
			return (1);
	}
	return (0);
}

void	*philo_daily_work(void *arg)
{
	t_data	*data_philo;
	int		i;

	i = 1;
	data_philo = (t_data *) arg;
	wait_for_others(data_philo);
	if (catch_one_philo(data_philo, i))
		return (arg);
	while (i <= data_philo->number_meals)
	{
		if (data_philo->dead != 0)
			break ;
		philo_eat(data_philo);
		if (data_philo->number_meals == i)
		{
			data_philo->finished = 1;
			break ;
		}
		if (data_philo->dead != 0)
			break ;
		philo_sleep(data_philo);
		philo_think(data_philo);
		i++;
	}
	return (arg);
}
