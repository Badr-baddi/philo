/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-bad <bael-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 18:11:33 by bael-bad          #+#    #+#             */
/*   Updated: 2025/08/03 17:58:39 by bael-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutexes(t_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&table->print_lock);
	pthread_mutex_destroy(&table->death_lock);
	while (i < table->total_diners)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
}
