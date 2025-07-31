/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mounitor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-bad <bael-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 17:51:12 by bael-bad          #+#    #+#             */
/*   Updated: 2025/07/31 16:38:20 by bael-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *monitor(void *arg)
{
    t_table *table = (t_table *)arg;
    size_t current_time;
    size_t time_since_meal;

    while (1)
    {
        current_time = get_current_time();
        for (int i = 0; i < table->total_diners; i++)
        {
            pthread_mutex_lock(&table->death_lock);
            if (table->diners[i].last_meal_time == 0)
                time_since_meal = get_current_time() - table->start_time;
            else
                time_since_meal = get_current_time() - table->diners[i].last_meal_time;
            pthread_mutex_unlock(&table->death_lock);
            
            if (time_since_meal > table->time_to_die)
            {
                pthread_mutex_lock(&table->death_lock);
                table->someone_died = 1;
                pthread_mutex_unlock(&table->death_lock);
                pthread_mutex_lock(&table->print_lock);
                printf("%lld %d died\n", 
                    current_time - table->start_time, 
                    table->diners[i].id);
                pthread_mutex_unlock(&table->print_lock);
                return (NULL);
            }
            pthread_mutex_unlock(&table->death_lock);
        }
        usleep(500);
    }
    return (NULL);
}
