/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhoerger <lhoerger@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 11:02:08 by lhoerger          #+#    #+#             */
/*   Updated: 2021/11/07 17:54:06 by lhoerger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*copy_global_data(t_data *global_data, int i)
{
	t_data	*data_philo;

	data_philo = malloc(sizeof(t_data));
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

void	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	data->total_mutexes = malloc(sizeof(pthread_mutex_t *)
			* data->number_philo_total);
	while (i < data->number_philo_total)
	{
		data->total_mutexes[i] = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init((data->total_mutexes[i]), NULL);
		i++;
	}
}

void	ft_free_1d(void **to_free)
{
	if (*to_free == NULL)
		return ;
	free(*to_free);
	*to_free = NULL;
}

void	ft_free_2d(void ***to_free)
{
	int	i;

	if (*to_free == NULL)
		return ;
	i = 0;
	while ((*to_free)[i] != NULL)
	{
		free((*to_free)[i]);
		(*to_free)[i] = NULL;
		i++;
	}
	free(*to_free);
	*to_free = NULL;
}

void	free_mutexes(t_data *data)
{
	int	i;

	i = 0;
	
	while (i < data->number_philo_total)
	{
		//write(1, "kommt hier an\n", 14);
		//printf("test %p\n", data->total_mutexes);
		pthread_mutex_destroy(data->total_mutexes[i]);
		free(data->total_mutexes[i]);
		data->total_mutexes[i] = NULL;
		i++;
	}
	free(data->total_mutexes);
	data->total_mutexes = NULL;
}


void free_data_philo(t_data *global_data, t_data **data)
{
	int	i;

	i = 0;
	while (i < global_data->number_philo_total)
	{
				write(1, "kommt hier an\n", 14);
		printf("number_philo_total: %i test %p\n", global_data->number_philo_total, data[i]);
		free(data[i]);
		data[i] = NULL;
		i++;
	}
	write(1, "hier\n", 5);
	free(data);
	data = NULL;
}
void	free_data(t_data *global_data, t_data **data_philo, pthread_t *th)
{
	free(th);
	th = NULL;
	//ft_free_2d((void ***) &data_philo);
	free_data_philo(global_data, data_philo);
	free_mutexes(global_data);
}

int	create_philos(t_data *global_data)
{
	pthread_t				*th;
	int						i;
	t_data					**data_philo;
	static pthread_mutex_t	mutex_print;

	pthread_mutex_init(&mutex_print, NULL);
	i = 0;
	data_philo = malloc(sizeof(t_data *) * global_data->number_philo_total);
	ft_bzero(data_philo, sizeof(*data_philo));
	th = malloc(sizeof(pthread_t) * global_data->number_philo_total + 1);
	init_mutexes(global_data);
	while (i < global_data->number_philo_total)
	{
		data_philo[i] = copy_global_data(global_data, i);
		data_philo[i]->mutex_print = &mutex_print;
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
	pthread_mutex_destroy(&mutex_print);
	free_data(global_data, data_philo, th);
	return (0);
}
