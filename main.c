/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhoerger <lhoerger@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 17:08:36 by lhoerger          #+#    #+#             */
/*   Updated: 2021/11/06 17:33:37 by lhoerger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	print_data(t_data *data)
{
	printf("data:\nnumber_philo : %i\n"
	"number_philo_total : %i\n"
	"time_to_die: %i\n"
	"time_to_eat: %i\n"
	"time_to_sleep: %i\n"
	"number meals: %i\n\n\n", 
	data->number_philo, 
	data->number_philo_total, 
	data->time_to_die, 
	data->time_to_eat, 
	data->time_to_sleep, 
	data->number_meals);
}

void protected_printf(t_data *data_philo, int mode)
{
	
	//printf("dead%i nr %i\n", data_philo->dead, data_philo->number_philo);
	
	pthread_mutex_lock(data_philo->mutex_print);
	if (data_philo->dead != 0)
	{
		pthread_mutex_unlock(data_philo->mutex_print);
		return ;
	}
	if (mode == TAKE_FORK)
			printf("%-10lu philosopher %i has taken a fork\n", data_philo->total_time, data_philo->number_philo);
	else if (mode == EATING)
		printf("%-10lu philosopher %i is eating\n", data_philo->total_time, data_philo->number_philo);
	pthread_mutex_unlock(data_philo->mutex_print);
}

int	counter_start(t_data *data)
{
	static int	cnt = 0;
	if (data->number_philo != 1)
		cnt++;
	return (cnt);
}
void sleep_thread(int time_to_sleep, t_data *data_philo)
{
	while (1)
	{
		gettimeofday(&data_philo->end_tv, NULL);
		data_philo->end_time = data_philo->end_tv.tv_sec * 1000 + data_philo->end_tv.tv_usec / 1000;
		if (data_philo->end_time - data_philo->start_time >= (unsigned long) time_to_sleep)
			break;
	}
	//printf("%lu last eat\n", data_philo->last_eat);
	data_philo->total_time =  data_philo->total_time + data_philo->end_time - data_philo->start_time;
}

void	calculate_start_time(t_data *data_philo)
{
	gettimeofday(&data_philo->start_tv, NULL);
	data_philo->start_time = data_philo->start_tv.tv_sec * 1000 + data_philo->start_tv.tv_usec / 1000;
	data_philo->total_time = data_philo->start_time - data_philo->start_time_first;
}
void	philo_eat(t_data *data_philo)
{
	if (data_philo->number_philo % 2 == 1)
	{
		//erst linkt dann rechts
		pthread_mutex_lock(data_philo->fork_left);
		calculate_start_time(data_philo);
		protected_printf(data_philo, TAKE_FORK);
		pthread_mutex_lock(data_philo->fork_right);
		calculate_start_time(data_philo);
		protected_printf(data_philo, TAKE_FORK);
		protected_printf(data_philo, EATING);
		//sleep solange es soll
		sleep_thread(data_philo->time_to_eat, data_philo);
		//usleep(500);
		data_philo->last_eat = data_philo->start_time + data_philo->time_to_eat;
		//printf("#################last eat changed to: %lu nr: %i\n", data_philo->last_eat, data_philo->number_philo);
		pthread_mutex_unlock(data_philo->fork_right);
		pthread_mutex_unlock(data_philo->fork_left);
		calculate_start_time(data_philo);
		//printf("%lu philosopher %i is finished eating\n", data_philo->total_time, data_philo->number_philo);
	}
	else
	{
		//erst rechts dann links
		pthread_mutex_lock(data_philo->fork_right);
		calculate_start_time(data_philo);
		protected_printf(data_philo, TAKE_FORK);
		pthread_mutex_lock(data_philo->fork_left);
		calculate_start_time(data_philo);
		protected_printf(data_philo, TAKE_FORK);
		calculate_start_time(data_philo);
		protected_printf(data_philo, EATING);
		//sleep solange es soll
		sleep_thread(data_philo->time_to_eat, data_philo);
		data_philo->last_eat = data_philo->start_time + data_philo->time_to_eat;
		//printf("#################last eat changed to: %lu nr: %i\n", data_philo->last_eat, data_philo->number_philo);
		//usleep(500);
		pthread_mutex_unlock(data_philo->fork_left);
		pthread_mutex_unlock(data_philo->fork_right);
		calculate_start_time(data_philo);
		//printf("%lu philosopher %i is finished eating\n", data_philo->total_time, data_philo->number_philo);
	}
}

void	philo_sleep(t_data *data_philo)
{
	calculate_start_time(data_philo);
	printf("%-10lu philosopher %i is sleeping\n", data_philo->total_time, data_philo->number_philo);
	sleep_thread(data_philo->time_to_sleep, data_philo);
}

void	philo_think(t_data *data_philo)
{
	calculate_start_time(data_philo);
	printf("%-10lu philosopher %i is thinking\n", data_philo->total_time, data_philo->number_philo);
}

void	get_start_time_first(t_data *data_philo)
{
	static unsigned long start_time_first = 0;
	struct timeval start_tv;

	if (start_time_first == 0 && data_philo->number_philo == 1)
	{
		gettimeofday(&start_tv, NULL);
		start_time_first = start_tv.tv_sec * 1000 + start_tv.tv_usec / 1000;
		
	}
	if (start_time_first != 0)
	{
		data_philo->last_eat = start_time_first;
		data_philo->start_time_first = start_time_first;
		//printf("%lu start time first\n", start_time_first);
	}
}

void	*philo_daily_work(void *arg)
{
	t_data	*data_philo;
	int	i;

	data_philo = (t_data*) arg;
	i = 1;
	//print_data(data_philo);
	counter_start(data_philo);
	if(data_philo->number_philo == 1)
	{
		while (1)
		{
			if (counter_start(data_philo) == data_philo->number_philo_total - 1)
				break;
		}
	}
	while (data_philo->start_time_first == 0)
	{
		get_start_time_first(data_philo);
	}
	while (data_philo->number_philo_total == 1)
	{
		if (i == 1)
		{
			i++;
			protected_printf(data_philo, TAKE_FORK);
		}
		if (data_philo->dead != 0)
			return (arg);
	}
	i = 1;
	//printf("%ul start time first, number philo %i\n", data_philo->start_time_first, data_philo->number_philo);
	while (i <= data_philo->number_meals)
	{
		if (data_philo->dead != 0)
			break;
		philo_eat(data_philo);
		if (data_philo->number_meals == i)
		{
			data_philo->finished = 1;
			break;
		}
		if (data_philo->dead != 0)
			break;
			philo_sleep(data_philo);
		if (data_philo->dead != 0)
			break;
			philo_think(data_philo);
		i++;
	}
	return (arg);
}

t_data	*copy_global_data(t_data *global_data, int i)
{
	t_data	*data_philo;

	data_philo = malloc(sizeof(t_data));
	bzero(data_philo, sizeof(*data_philo)); //bzero
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
	//printf("i: %i, fork_left %p, fork right %p\n", i, data_philo->fork_left, data_philo->fork_right);
	return (data_philo);
}
void	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	data->total_mutexes = malloc(sizeof(pthread_mutex_t *) * data->number_philo_total);
	while (i < data->number_philo_total)
	{
		data->total_mutexes[i] = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init((data->total_mutexes[i]), NULL);
		i++;
	}
}

void	*stalk_philos(void *arg)
{
	t_data	**data;
	int	i;
	struct timeval tv;
	unsigned long current_time;

	i = 0;
	data = (t_data **) arg;
	while (1)
	{
		
		gettimeofday(&tv, NULL);
		current_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
		if (current_time - data[i]->last_eat >= (unsigned long) data[0]->time_to_die && data[i]->finished != 1)
		{
			//printf("current_time:%lu, data->lasteat: %lu, sub: %lu, time to die: %i\n", current_time, data[i]->last_eat, current_time - data[i]->last_eat, data[0]->time_to_die);
			printf("%-10lu philosopher %i died\n",current_time - data[i]->start_time_first, i + 1);
			i = 0;
			while (i < data[0]->number_philo_total)
			{
				//printf("########## %i: nr: %i, dead, total: %i\n", i, data[i]->number_philo, data[i]->number_philo_total);
				data[i]->dead = 1;
				i++;
			}
			break;
		}
		i++;
		if (i == (*data)->number_philo_total)
			i = 0;
	}
	return (arg);
}
int	create_philos(t_data *global_data)
{
	pthread_t	*th;
	int	i;
	t_data	**data_philo;
	static pthread_mutex_t mutex_print;
	
	pthread_mutex_init(&mutex_print, NULL);
	i = 0;
	data_philo = malloc(sizeof(t_data * ) * global_data->number_philo_total);
	bzero(data_philo, sizeof(*data_philo));
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
	
	//create stalker
	if (pthread_create(&th[i], NULL, &stalk_philos, data_philo) != 0)
	{
		printf("Error while creating Thread\n");
		return (1);
	}
	i = 0;
	while (i < global_data->number_philo_total)
	{
		if (pthread_join(th[i], (void *) &data_philo) != 0)
		{
			printf("Error while joining Thread\n");
			return (1);
		}
		//free mutexes
		//free(data_philo);
		//data_philo = NULL;
		
		//printf("Thread %d has finished\n", i + 1);
		i++;
	}
	//stalker thread beenden fehlt noch
	pthread_mutex_destroy(&mutex_print);
	free(th);
	th = NULL;
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data data;
	
	bzero(&data, sizeof(data)); // Achtung bzero
	if (input_check(argc, argv, &data) == 1)
		return (1);
	//print_data(&data);
	create_philos(&data);
	
	return (0);
}