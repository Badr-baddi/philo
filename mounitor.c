/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mounitor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-bad <bael-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 17:51:12 by bael-bad          #+#    #+#             */
/*   Updated: 2025/08/02 17:28:50 by bael-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	all_ate_enough(t_table *table)
{
	int	i;

	if (table->must_eat <= 0)
		return (0);
	i = 0;
	while (i < table->total_diners)
	{
		pthread_mutex_lock(&table->death_lock);
		if (table->diners[i].meals_eaten < table->must_eat)
		{
			pthread_mutex_unlock(&table->death_lock);
			return (0);
		}
		pthread_mutex_unlock(&table->death_lock);
		i++;
	}
	return (1);
}

static int	check_death_1(t_table *table, size_t time)
{
	int	i;

	i = 0;
	while (i < table->total_diners)
	{
		pthread_mutex_lock(&table->death_lock);
		if (time - table->diners[i].last_meal_time > table->time_to_die)
		{
			table->someone_died = 1;
			pthread_mutex_unlock(&table->death_lock);
			pthread_mutex_lock(&table->print_lock);
			printf("%lld %d died\n", time - table->start_time,
				table->diners[i].id);
			pthread_mutex_unlock(&table->print_lock);
			return (1);
		}
		pthread_mutex_unlock(&table->death_lock);
		i++;
	}
	return (0);
}

static int	check_all_ate(t_table *table)
{
	if (all_ate_enough(table))
	{
		pthread_mutex_lock(&table->death_lock);
		table->someone_died = 1;
		pthread_mutex_unlock(&table->death_lock);
		return (1);
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_table	*table;
	size_t	time;

	table = (t_table *)arg;
	while (1)
	{
		usleep(1000);
		time = get_current_time();
		if (check_death_1(table, time) || check_all_ate(table))
			break ;
	}
	return (NULL);
}
