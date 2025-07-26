/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_think.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-bad <bael-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 19:37:13 by bael-bad          #+#    #+#             */
/*   Updated: 2025/07/26 19:39:39 by bael-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    ft_think(t_philo *philo)
{
    ft_message("is_thinking", philo, philo->id);
    if (philo->num_of_philos % 2)
        ft_usleep(1);
}