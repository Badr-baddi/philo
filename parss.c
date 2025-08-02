/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parss.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-bad <bael-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 11:45:04 by bael-bad          #+#    #+#             */
/*   Updated: 2025/08/02 17:19:05 by bael-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_diner *diner, const char *msg)
{
	pthread_mutex_lock(&diner->table->death_lock);
	if (diner->table->someone_died)
	{
		pthread_mutex_unlock(&diner->table->death_lock);
		return ;
	}
	pthread_mutex_unlock(&diner->table->death_lock);
	pthread_mutex_lock(&diner->table->print_lock);
	printf("%lld %d %s\n", get_current_time() - diner->table->start_time,
		diner->id, msg);
	pthread_mutex_unlock(&diner->table->print_lock);
}

int	parss(char *av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (av[i] < '0' || av[i] > '9')
		{
			printf("THE INPUT IS NOT CORRECT :(\n");
			return (0);
		}
		i++;
	}
	return (1);
}
