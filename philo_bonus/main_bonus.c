/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhoerger <lhoerger@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 14:54:21 by lhoerger          #+#    #+#             */
/*   Updated: 2021/11/12 16:18:34 by lhoerger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	handle_processes(t_data *data)
{
	int	i;
	int	id;

	i = 0;
	while (i < data->number_philo_total)
	{
		data->number_philo = i + 1;
		id = fork();
		if (id < 0)
			exit(1);
		data->pid = id;
		if (id == 0)
		{
			daily_work(data);
			exit(1);
		}
		i++;
	}
	if (waitpid(-1, 0, 0) != -1)
	{
		usleep(10000);
		if (data->number_philo != 1)
			kill(0, SIGINT);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data			data;
	struct timeval	time_tv;

	ft_bzero(&data, sizeof(data));
	if (input_check(argc, argv, &data) == 1)
		return (1);
	data.forks = sem_open("/forks", O_CREAT, 0644, data.number_philo_total);
	data.sem_printf = sem_open("/sem_print", O_CREAT, 0644, 1);
	sem_unlink("/forks");
	sem_unlink("/sem_print");
	gettimeofday(&time_tv, NULL);
	data.start_time_first = time_tv.tv_sec * 1000 + time_tv.tv_usec / 1000;
	if (handle_processes(&data) == 1)
		return (0);
	sem_close(data.forks);
	sem_close(data.sem_printf);
	return (0);
}
