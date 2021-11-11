/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daily_work_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhoerger <lhoerger@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 10:04:39 by lhoerger          #+#    #+#             */
/*   Updated: 2021/11/11 10:04:47 by lhoerger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	coordinate_philos(t_data *data_philo, int *i)
{
	if (data_philo->number_philo_total > 30)
		usleep(650);
	usleep(200);
	*i = *i + 1;
}

int	make_philos_ready(t_data *data_philo, int i)
{
	wait_for_others(data_philo);
	if (catch_one_philo(data_philo, i))
		return (1);
	if (data_philo->number_philo % 2 == 0)
		usleep(10000);
	return (0);
}
