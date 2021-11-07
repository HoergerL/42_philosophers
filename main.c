/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhoerger <lhoerger@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 17:08:36 by lhoerger          #+#    #+#             */
/*   Updated: 2021/11/07 15:45:36 by lhoerger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


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
		//calculate_start_time(data_philo);
		protected_printf(data_philo, TAKE_FORK);
		pthread_mutex_lock(data_philo->fork_right);
		//calculate_start_time(data_philo);
		protected_printf(data_philo, TAKE_FORK);
		protected_printf(data_philo, EATING);
		//sleep solange es soll
		sleep_thread(data_philo->time_to_eat, data_philo);
		//usleep(500);
		//printf("prev last eat: %lu now last_eat: %lu\n, diff: %lu", data_philo->last_eat, data_philo->start_time + data_philo->time_to_eat, data_philo->start_time + data_philo->time_to_eat - data_philo->last_eat);
		data_philo->last_eat = data_philo->start_time + data_philo->time_to_eat;
		//printf("#################last eat changed to: %lu nr: %i\n", data_philo->last_eat, data_philo->number_philo);
		pthread_mutex_unlock(data_philo->fork_right);
		pthread_mutex_unlock(data_philo->fork_left);
	}
	else
	{
		//erst rechts dann links
		pthread_mutex_lock(data_philo->fork_right);
		
		protected_printf(data_philo, TAKE_FORK);
		pthread_mutex_lock(data_philo->fork_left);
		//calculate_start_time(data_philo);
		protected_printf(data_philo, TAKE_FORK);
		//calculate_start_time(data_philo);
		protected_printf(data_philo, EATING);
		//sleep solange es soll
		sleep_thread(data_philo->time_to_eat, data_philo);
		//printf("prev last eat: %lu now last_eat: %lu\n, diff: %lu", data_philo->last_eat, data_philo->start_time + data_philo->time_to_eat, data_philo->start_time + data_philo->time_to_eat - data_philo->last_eat);
		data_philo->last_eat = data_philo->start_time + data_philo->time_to_eat;
		//printf("#################last eat changed to: %lu nr: %i\n", data_philo->last_eat, data_philo->number_philo);
		//usleep(500);
		pthread_mutex_unlock(data_philo->fork_left);
		pthread_mutex_unlock(data_philo->fork_right);
		//calculate_start_time(data_philo);
		//printf("%lu philosopher %i is finished eating\n", data_philo->total_time, data_philo->number_philo);
	}
}

void	philo_sleep(t_data *data_philo)
{
	//calculate_start_time(data_philo);
	protected_printf(data_philo, SLEEPING);
	sleep_thread(data_philo->time_to_sleep, data_philo);
}

void	philo_think(t_data *data_philo)
{
	//calculate_start_time(data_philo);
	protected_printf(data_philo, THINKING);
}

int	get_start_time_first(t_data *data_philo, int stalker)
{
	static unsigned long start_time_first = 0;
	struct timeval start_tv;
	static int	cnt = 0;

	if (start_time_first == 0 && data_philo->number_philo == 1)
	{
		gettimeofday(&start_tv, NULL);
		start_time_first = start_tv.tv_sec * 1000 + start_tv.tv_usec / 1000;
		
	}
	if (start_time_first != 0 && stalker != 1)
	{
		data_philo->last_eat = start_time_first;
		data_philo->start_time_first = start_time_first;
		cnt++;
		//printf("%lu start time first\n", start_time_first);
	}
	return (cnt);
}

int	catch_one_philo(t_data *data_philo, int i)
{
	while (data_philo->number_philo_total == 1)
	{
		if (i == 1)
		{
			i++;
			protected_printf(data_philo, TAKE_FORK);
		}
		if (data_philo->dead != 0)
			return (1);
	}
	return (0);
}

void	*philo_daily_work(void *arg)
{
	t_data	*data_philo;
	int	i;

	data_philo = (t_data*) arg;
	i = 1;
	//print_data(data_philo);
	//printf("philo %i was created\n", data_philo->number_philo);
	//fflush(stdout);
	counter_start(data_philo);
	if(data_philo->number_philo == 1)
	{
		while (1)
		{
			if (counter_start(data_philo) == data_philo->number_philo_total - 1)
			{
				//printf("$$$$$$$$$$$$$$$$$$$$$$$$all philos are created\n");
				//fflush(stdout);
				break;
			}
		}
	}
	//printf("xxxxxxxxxxxxphil %i start time = %lu\n", data_philo->number_philo, data_philo->start_time_first);
	while (data_philo->start_time_first == 0)
	{
		//printf("%i wartet\n", data_philo->number_philo);
		//fflush(stdout);
		get_start_time_first(data_philo, 0);
	}
		
	if (catch_one_philo(data_philo, i))
		return (arg);
	//printf("philo %i starts daily life\n", data_philo->number_philo);
	//fflush(stdout);
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

void	*stalk_philos(void *arg)
{
	t_data	**data;
	int	i;
	struct timeval tv;
	unsigned long current_time;

	i = 0;
	data = (t_data **) arg;
	//printf("#####stalker was created\n");
	//fflush(stdout);
	while (get_start_time_first(data[data[i]->number_philo_total - 1], 1) < data[i]->number_philo_total - 2)
	{
		continue ;
	}
	usleep(8000);
	//printf("#####stalker starts working\n");
	//fflush(stdout);
	while (1)
	{
		gettimeofday(&tv, NULL);
		current_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
		//printf("current_time:%lu, data->lasteat: %lu, sub: %lu, time to die: %i\n", current_time, data[i]->last_eat, current_time - data[i]->last_eat, data[0]->time_to_die);
		//fflush(stdout);
		if (current_time - data[i]->last_eat > (unsigned long) data[0]->time_to_die && data[i]->finished != 1)
		{
			//printf("current_time:%lu, data->lasteat: %lu, sub: %lu, time to die: %i\n", current_time, data[i]->last_eat, current_time - data[i]->last_eat, data[0]->time_to_die);
			protected_printf(data[i], DEAD);
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