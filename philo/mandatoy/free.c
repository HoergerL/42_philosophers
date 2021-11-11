/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhoerger <lhoerger@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 18:36:04 by lhoerger          #+#    #+#             */
/*   Updated: 2021/11/07 18:37:56 by lhoerger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_philo_total)
	{
		pthread_mutex_destroy(data->total_mutexes[i]);
		free(data->total_mutexes[i]);
		data->total_mutexes[i] = NULL;
		i++;
	}
	free(data->total_mutexes);
	data->total_mutexes = NULL;
}

void	free_data_philo(t_data *global_data, t_data **data)
{
	int	i;

	i = 0;
	while (i < global_data->number_philo_total)
	{
		free(data[i]);
		data[i] = NULL;
		i++;
	}
	free(data);
	data = NULL;
}

void	free_data(t_data *global_data, t_data **data_philo, pthread_t *th)
{
	free(th);
	th = NULL;
	free_data_philo(global_data, data_philo);
	free_mutexes(global_data);
}
