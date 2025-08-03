/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-bad <bael-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 16:14:48 by bael-bad          #+#    #+#             */
/*   Updated: 2025/08/03 17:26:42 by bael-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_threads(t_table *table)
{
	int	i;

	i = 0;
	table->start_time = get_current_time();
	while (i < table->total_diners)
	{
		table->diners[i].last_meal_time = table->start_time;
		if (pthread_create(&table->diners[i].thread,
				NULL, routine, &table->diners[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

void	join_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->total_diners)
	{
		pthread_join(table->diners[i].thread, NULL);
		i++;
	}
}
