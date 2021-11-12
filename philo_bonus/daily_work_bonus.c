/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daily_work_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhoerger <lhoerger@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 08:27:22 by lhoerger          #+#    #+#             */
/*   Updated: 2021/11/12 08:29:39 by lhoerger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_eat(t_data *data)
{
	sem_wait(data->forks);
	protected_printf(data, TAKE_FORK);
	sem_wait(data->forks);
	protected_printf(data, TAKE_FORK);
	protected_printf(data, EATING);
	create_killer(data);
	ft_usleep(data->time_to_eat);
	sem_post(data->forks);
	sem_post(data->forks);
}

void	philo_sleep(t_data *data)
{
	protected_printf(data, SLEEPING);
	ft_usleep(data->time_to_eat);
}

void	philo_think(t_data *data)
{
	protected_printf(data, THINKING);
}

int	catch_one_philo(t_data *data, int i)
{
	while (data->number_philo_total == 1)
	{
		if (i == 1)
		{
			i++;
			printf("0 %i has taken a fork\n", data->number_philo);
			ft_usleep(data->time_to_die);
			printf("%i %i died\n", data->time_to_die, data->number_philo);
			return (1);
		}
	}
	return (0);
}

void	daily_work(t_data *data)
{
	int	i;

	i = 1;
	if (data->number_philo % 2 == 1)
		ft_usleep(50);
	if (catch_one_philo(data, i) == 1)
		return ;
	while (i <= data->number_meals)
	{
		philo_eat(data);
		if (data->number_meals == i)
			break ;
		philo_sleep(data);
		philo_think(data);
		if (data->number_philo_total > 30)
			usleep(650);
		usleep(200);
		i++;
	}
}
