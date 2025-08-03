/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-bad <bael-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 15:24:08 by bael-bad          #+#    #+#             */
/*   Updated: 2025/08/03 17:24:34 by bael-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds, t_table *table)
{
	size_t	start;
	size_t	elapsed;

	start = get_current_time();
	while (1)
	{
		if (is_simulation_over(table))
			return (1);
		elapsed = get_current_time() - start;
		if (elapsed >= milliseconds)
			break ;
		usleep(100);
	}
	return (0);
}