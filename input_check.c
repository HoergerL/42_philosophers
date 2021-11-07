/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhoerger <lhoerger@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 17:25:10 by lhoerger          #+#    #+#             */
/*   Updated: 2021/11/07 16:51:52 by lhoerger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h" 

int	ft_isdigit(int c)
{
	 	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	return (0);
}

size_t	ft_strlen(const char *s)
{
	int	cnt;

	cnt = 0;
	while (s[cnt] != '\0')
	{
		cnt++;
	}
	return (cnt);
}

void	get_input(int argc, char *argv[], t_data *data)
{
	data->number_philo_total = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->number_meals = ft_atoi(argv[5]);
	else
		data->number_meals = INT_MAX;
}

int	check_digit(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!(ft_isdigit(argv[i][j]) || argv[i][j] == '+'))
			{
				printf("incorrect input\n");
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	input_check(int argc, char *argv[], t_data *data)
{
	if (!(argc == 5 || argc == 6))
	{
		printf("wrong number of arguments\n");
		return (1);
	}
	if (check_digit(argc, argv) == 1)
		return (1);
	get_input(argc, argv, data);
	if (data->number_philo_total < 1 || data->time_to_die < 0
		|| data->time_to_eat < 0 || data->time_to_sleep < 0
		|| data->number_philo_total > 250 || data->number_meals < 0)
	{
		printf("too less philos\n");
		return (1);
	}
	return (0);
}
