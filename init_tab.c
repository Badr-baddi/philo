/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-bad <bael-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:45:22 by bael-bad          #+#    #+#             */
/*   Updated: 2025/08/02 17:13:05 by bael-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutexes(t_table *table)
{
	int	i;

	if (pthread_mutex_init(&table->print_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&table->death_lock, NULL) != 0)
		return (1);
	i = 0;
	while (i < table->total_diners)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

void	init_diners(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->total_diners)
	{
		table->diners[i].id = i + 1;
		table->diners[i].meals_eaten = 0;
		table->diners[i].last_meal_time = 0;
		table->diners[i].left_fork = &table->forks[i];
		table->diners[i].right_fork
			= &table->forks[(i + 1) % table->total_diners];
		table->diners[i].table = table;
		i++;
	}
}
