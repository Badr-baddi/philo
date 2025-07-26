/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parss.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-bad <bael-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 11:45:04 by bael-bad          #+#    #+#             */
/*   Updated: 2025/07/26 22:41:45 by bael-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_message(char *msg, t_philo *philo, int id)
{
	pthread_mutex_lock(&philo->program.write_lock);
	if (!philo->program.dead_flag || ft_strcmp(msg, "died") == 0)
		printf("%ld %d %s\n", get_time() - philo->start_time, id, msg);
	pthread_mutex_unlock(&philo->program.write_lock);
}

int	is_dead(t_philo *philo)
{
	long	now;

	pthread_mutex_lock(&philo->program.dead_lock);
	if (philo->program.dead_flag)
	{
		pthread_mutex_unlock(&philo->program.dead_lock);
		return (1);
	}
	now = get_time();
	if ((now - philo->last_meal) > philo->time_to_die)
	{
		ft_message("died", philo, philo->id);
		philo->program.dead_flag = 1;
		pthread_mutex_unlock(&philo->program.dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->program.dead_lock);
	return (0);
}

int parss(char *av)
{
    int i = 0;

    while (av[i])
    {
        if (av[i] < '0' || av[i] > '9')
        {
            printf("THE INPUT IS NOT CORRECT :(\n");
            return 0;
        }
        i++;
    }
    printf("THE INPUT IS TRUE :)\n");
    printf("%s\n", av);
    return 1;
}
