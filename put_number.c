/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_number.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhoerger <lhoerger@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 17:04:13 by lhoerger          #+#    #+#             */
/*   Updated: 2021/10/29 17:30:38 by lhoerger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "philo.h"

int	ft_do_calculation(int n, int new_n)
{
	if (n < 0)
	{
		write (1, "-", 1);
		n = -n;
	}
	if (n / 10 == 0)
	{
		n = n + 48;
		write(1, &n, 1);
		return (0);
	}
	new_n = n / 10;
	ft_putnbr(new_n);
	n = (n % 10) + 48;
	write(1, &n, 1);
	return (1);
}

void	ft_putnbr(int n)
{
	int	new_n;

	new_n = 0;
	if (n == -2147483648)
	{
		write(1, "-2147483648", ft_strlen("-2147483648"));
		return ;
	}
	if (!(ft_do_calculation(n, new_n)))
		return ;
}
