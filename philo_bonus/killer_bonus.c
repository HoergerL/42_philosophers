/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   killer_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhoerger <lhoerger@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 08:24:19 by lhoerger          #+#    #+#             */
/*   Updated: 2021/11/12 15:55:11 by lhoerger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*check_philo(void *arg)
{
	t_data			*data;
	unsigned long	last_eat;

	data = (t_data *) arg;
	last_eat = data->last_eat;
	ft_usleep(data->time_to_die + 1);
	if (last_eat == data->last_eat)
	{
		protected_printf(data, DEAD);
		kill(0, SIGINT);
	}
	return (arg);
}

void	create_killer(t_data *data)
{
	pthread_t	th;

	data->last_eat = data->start_time;
	if (pthread_create(&th, NULL, &check_philo, (void *) data) != 0)
	{
		printf("Error while creating Thread\n");
		exit(1);
	}
	pthread_detach(th);
}
