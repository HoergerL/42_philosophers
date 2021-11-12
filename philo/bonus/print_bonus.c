/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhoerger <lhoerger@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 08:25:48 by lhoerger          #+#    #+#             */
/*   Updated: 2021/11/12 08:30:32 by lhoerger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	protected_printf(t_data *phi, int mode)
{
	static int	print = 1;

	sem_wait(phi->sem_printf);
	if (print != 1)
	{
		sem_post(phi->sem_printf);
		return ;
	}
	calculate_start_time(phi);
	if (mode == TAKE_FORK)
		printf("%lu %i has taken a fork\n", phi->total_time, phi->number_philo);
	else if (mode == EATING)
		printf("%lu %i is eating\n", phi->total_time, phi->number_philo);
	else if (mode == SLEEPING)
		printf("%lu %i is sleeping\n", phi->total_time, phi->number_philo);
	else if (mode == THINKING)
		printf("%lu %i is thinking\n", phi->total_time, phi->number_philo);
	else if (mode == DEAD)
	{
		printf("%lu %i died\n", phi->total_time, phi->number_philo);
		print = 0;
	}
	if (print != 0)
		sem_post(phi->sem_printf);
}
