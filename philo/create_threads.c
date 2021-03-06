/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhoerger <lhoerger@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 11:02:08 by lhoerger          #+#    #+#             */
/*   Updated: 2021/11/12 14:55:42 by lhoerger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*copy_global_data(t_data *global_data, int i)
{
	t_data	*data_philo;

	data_philo = malloc(sizeof(t_data));
	if (!data_philo)
		return (NULL);
	ft_bzero(data_philo, sizeof(*data_philo));
	data_philo->number_philo = i + 1;
	data_philo->number_meals = global_data->number_meals;
	data_philo->number_philo_total = global_data->number_philo_total;
	data_philo->time_to_die = global_data->time_to_die;
	data_philo->time_to_eat = global_data ->time_to_eat;
	data_philo->time_to_sleep = global_data->time_to_sleep;
	data_philo->fork_right = global_data->total_mutexes[i];
	if (data_philo->number_philo_total == data_philo->number_philo)
		data_philo->fork_left = global_data->total_mutexes[0];
	else
		data_philo->fork_left = global_data->total_mutexes[i + 1];
	return (data_philo);
}

int	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	data->total_mutexes = malloc(sizeof(pthread_mutex_t *)
			* data->number_philo_total);
	if (!data->total_mutexes)
		return (1);
	while (i < data->number_philo_total)
	{
		data->total_mutexes[i] = malloc(sizeof(pthread_mutex_t));
		if (!data->total_mutexes[i])
			return (1);
		pthread_mutex_init((data->total_mutexes[i]), NULL);
		i++;
	}
	return (0);
}

int	create_threads(t_data *global_data, t_data **data_philo,
	pthread_mutex_t *mutex_print, pthread_t *th)
{
	int	i;

	i = 0;
	while (i < global_data->number_philo_total)
	{
		data_philo[i] = copy_global_data(global_data, i);
		if (data_philo[i] == NULL)
			return (1);
		data_philo[i]->mutex_print = mutex_print;
		if (pthread_create(&th[i], NULL, &philo_daily_work, data_philo[i]) != 0)
		{
			printf("Error while creating Thread\n");
			return (1);
		}
		i++;
	}
	if (pthread_create(&th[i], NULL, &stalk_philos, data_philo) != 0)
	{
		printf("Error while creating Thread\n");
		return (1);
	}
	return (0);
}

int	join_philos(t_data *global_data, pthread_t *th)
{
	int	i;

	i = 0;
	while (i < global_data->number_philo_total + 1)
	{
		if (pthread_join(th[i], NULL) != 0)
		{
			printf("Error while joining Thread\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	create_philos(t_data *global_data)
{
	pthread_t				*th;
	t_data					**data_philo;
	static pthread_mutex_t	mutex_print;

	pthread_mutex_init(&mutex_print, NULL);
	data_philo = malloc(sizeof(t_data *) * global_data->number_philo_total);
	th = malloc(sizeof(pthread_t) * global_data->number_philo_total + 1);
	if (!data_philo || !th)
		return (1);
	ft_bzero(data_philo, sizeof(*data_philo));
	if (init_mutexes(global_data) == 1)
		return (1);
	if (create_threads(global_data, data_philo, &mutex_print, th) == 1)
		return (1);
	if (join_philos(global_data, th) == 1)
		return (1);
	pthread_mutex_destroy(&mutex_print);
	free_data(global_data, data_philo, th);
	return (0);
}
/*
./philo 1 800 200 200
die after 800 milliseconds
./philo 2 420 200 200
run for ever
./philo 5 800 200 200
run for ever
./philo 5 800 200 200 7
end after 7 meals_per_philo
./philo 4 410 200 200
run for ever
./philo 4 310 200 100
1 must die
./philo 3 550 200 200
1 must die
./philo 30 550 200 200
run for ever
./philo 30 800 200 200 7
end after 7 meals_per_philo
./philo 99 620 200 200
run for ever
./philo 98 440 200 200
run for ever
./philo 198 440 200 200
run for ever
./philo 199 620 200 200
run for ever
*/