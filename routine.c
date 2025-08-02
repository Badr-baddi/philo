/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-bad <bael-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 16:05:42 by bael-bad          #+#    #+#             */
/*   Updated: 2025/08/02 17:15:17 by bael-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_table *table)
{
	int		i;
	size_t	current_time;

	i = 0;
	while (i < table->total_diners)
	{
		current_time = get_current_time() - table->start_time;
		pthread_mutex_lock(&table->death_lock);
		if ((current_time - table->diners[i].last_meal_time)
			> table->time_to_die)
		{
			pthread_mutex_unlock(&table->death_lock);
			pthread_mutex_lock(&table->print_lock);
			printf("%lld %d died\n", current_time - table->start_time,
				table->diners[i].id);
			pthread_mutex_unlock(&table->print_lock);
			table->someone_died = 1;
			return (1);
		}
		pthread_mutex_unlock(&table->death_lock);
		i++;
	}
	return (0);
}

static int	check_someone_died(t_table *table)
{
	int	died;

	pthread_mutex_lock(&table->death_lock);
	died = table->someone_died;
	pthread_mutex_unlock(&table->death_lock);
	return (died);
}

static void	take_forks_and_eat(t_diner *diner)
{
	pthread_mutex_lock(diner->left_fork);
	print_message(diner, "has taken a fork");
	pthread_mutex_lock(diner->right_fork);
	print_message(diner, "has taken a fork");
	print_message(diner, "is eating");
	pthread_mutex_lock(&diner->table->death_lock);
	diner->last_meal_time = get_current_time();
	diner->meals_eaten++;
	pthread_mutex_unlock(&diner->table->death_lock);
	ft_usleep(diner->table->time_to_eat, diner);
	pthread_mutex_unlock(diner->left_fork);
	pthread_mutex_unlock(diner->right_fork);
}

static void	sleep_and_think(t_diner *diner)
{
	print_message(diner, "is sleeping");
	ft_usleep(diner->table->time_to_sleep, diner);
	print_message(diner, "is thinking");
}

void	*routine(void *arg)
{
	t_diner	*diner;

	diner = (t_diner *)arg;
	if (diner->id % 2 == 0)
		usleep(100);
	if (diner->table->total_diners == 1)
	{
		pthread_mutex_lock(diner->left_fork);
		print_message(diner, "has taken a fork");
		ft_usleep(diner->table->time_to_die, diner);
		pthread_mutex_unlock(diner->left_fork);
		return (NULL);
	}
	while (1)
	{
		if (check_someone_died(diner->table))
			break ;
		take_forks_and_eat(diner);
		if (check_someone_died(diner->table))
			break ;
		sleep_and_think(diner);
		if (check_someone_died(diner->table))
			break ;
	}
	return (NULL);
}
