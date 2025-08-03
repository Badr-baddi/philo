/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-bad <bael-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 16:05:42 by bael-bad          #+#    #+#             */
/*   Updated: 2025/08/03 17:24:14 by bael-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	ft_usleep(diner->table->time_to_eat, diner->table);
	pthread_mutex_unlock(diner->left_fork);
	pthread_mutex_unlock(diner->right_fork);
}

static void	sleep_and_think(t_diner *diner)
{
	print_message(diner, "is sleeping");
	ft_usleep(diner->table->time_to_sleep, diner->table);
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
		ft_usleep(diner->table->time_to_die, diner->table);
		pthread_mutex_unlock(diner->left_fork);
		return (NULL);
	}
	while (1)
	{
		if (is_simulation_over(diner->table))
			break ;
		take_forks_and_eat(diner);
		if (is_simulation_over(diner->table))
			break ;
		sleep_and_think(diner);
		if (is_simulation_over(diner->table))
			break ;
	}
	return (NULL);
}
