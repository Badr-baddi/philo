/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dream.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-bad <bael-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 17:26:11 by bael-bad          #+#    #+#             */
/*   Updated: 2025/07/27 20:37:34 by bael-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	ft_delay(t_philo *philo, size_t time_in_ms)
// {
// 	size_t	start;

// 	start = get_time();
// 	while (!is_dead(philo))
// 	{
// 		if (get_time() - start >= time_in_ms)
// 			break;
// 		usleep(100); // Sleep 100 microseconds to reduce CPU usage
// 	}
// }

void	ft_delay(size_t time_in_ms)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < time_in_ms)
		usleep(100);
}

void    ft_sleep(t_philo *philo)
{
    ft_message("is sleeping", philo, philo->id);
    ft_delay(philo->time_to_sleep);
}