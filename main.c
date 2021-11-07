/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhoerger <lhoerger@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 17:08:36 by lhoerger          #+#    #+#             */
/*   Updated: 2021/11/07 18:43:52 by lhoerger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	kill_util(t_data **data, int i)
{
	protected_printf(data[i], DEAD);
	i = 0;
	while (i < data[0]->number_philo_total)
	{
		data[i]->dead = 1;
		i++;
	}
}

void	kill_philos(t_data **data)
{
	struct timeval	tv;
	unsigned long	current_time;
	int				i;

	i = 0;
	while (1)
	{
		gettimeofday(&tv, NULL);
		current_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
		if (data[i]->finished == 1)
			break ;
		if (current_time - data[i]->last_eat
			> (unsigned long) data[0]->time_to_die && data[i]->finished != 1)
		{
			kill_util(data, i);
			break ;
		}
		i++;
		if (i == (*data)->number_philo_total)
			i = 0;
	}
}

void	*stalk_philos(void *arg)
{
	t_data	**data;

	data = (t_data **) arg;
	while (get_start_time_first(data[data[0]->number_philo_total - 1], 1)
		< data[0]->number_philo_total - 2)
	{
		continue ;
		usleep(100);
	}
	usleep(8000);
	kill_philos(data);
	return (arg);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	ft_bzero(&data, sizeof(data));
	if (input_check(argc, argv, &data) == 1)
		return (1);
	create_philos(&data);
	return (0);
}
