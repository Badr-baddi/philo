/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parss.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-bad <bael-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 11:45:04 by bael-bad          #+#    #+#             */
/*   Updated: 2025/08/03 17:58:06 by bael-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_diner *diner, const char *msg)
{
	if (is_simulation_over(diner->table))
		return ;
	pthread_mutex_lock(&diner->table->print_lock);
	if (is_simulation_over(diner->table))
	{
		pthread_mutex_unlock(&diner->table->print_lock);
		return ;
	}
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
