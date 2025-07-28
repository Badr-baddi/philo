// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   ft_eat.c                                           :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: bael-bad <bael-bad@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/07/26 16:55:39 by bael-bad          #+#    #+#             */
// /*   Updated: 2025/07/27 20:37:52 by bael-bad         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "philo.h"

// void ft_eat(t_philo *philo)
// {
//     // Only one philosopher
//     if (philo->num_of_philos == 1)
//     {
//         pthread_mutex_lock(philo->r_fork);
//         ft_message("has taken a fork", philo, philo->id);
//         ft_delay(philo->time_to_die);
//         pthread_mutex_unlock(philo->r_fork);
//         return;
//     }
//     //DEADLOCK AVOIDANCE: alternate fork order based on ID
//     // if (philo->id % 2 == 0)
//     // {
//     //     pthread_mutex_lock(philo->l_fork);
//     //     ft_message("has taken a fork", philo, philo->id);
//     //     pthread_mutex_lock(philo->r_fork);
//     //     ft_message("has taken a fork", philo, philo->id);
//     // }
//     // else
//     // {
//     //     pthread_mutex_lock(philo->r_fork);
//     //     ft_message("has taken a fork", philo, philo->id);
//     //     pthread_mutex_lock(philo->l_fork);
//     //     ft_message("has taken a fork", philo, philo->id);
//     // }
//     //Eating
//     pthread_mutex_lock(philo->meal_lock);
//     philo->eating = 1;
//     philo->last_meal = get_time();
//     philo->meals_eaten++;
//     pthread_mutex_unlock(philo->meal_lock);
//     ft_message("is eating", philo, philo->id);
//     pthread_mutex_lock(philo->meal_lock);
//     philo->eating = 0;
//     pthread_mutex_unlock(philo->meal_lock);
//     ft_delay(philo->time_to_eat);
//     pthread_mutex_unlock(philo->l_fork);
//     pthread_mutex_unlock(philo->r_fork);
// }

void ft_eat(t_philo *philo)
{
    // Only one philosopher
    if (philo->num_of_philos == 1)
    {
        pthread_mutex_lock(philo->r_fork);
        ft_message("has taken a fork", philo, philo->id);
        ft_delay(philo->time_to_die);
        pthread_mutex_unlock(philo->r_fork);
        return;
    }
    
    // DEADLOCK AVOIDANCE: even philosophers pick up left fork first, odd pick up right fork first
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(philo->l_fork);
        ft_message("has taken a fork", philo, philo->id);
        pthread_mutex_lock(philo->r_fork);
        ft_message("has taken a fork", philo, philo->id);
    }
    else
    {
        pthread_mutex_lock(philo->r_fork);
        ft_message("has taken a fork", philo, philo->id);
        pthread_mutex_lock(philo->l_fork);
        ft_message("has taken a fork", philo, philo->id);
    }
    
    // Eating
    pthread_mutex_lock(philo->meal_lock);
    philo->eating = 1;
    philo->last_meal = get_time();
    philo->meals_eaten++;
    pthread_mutex_unlock(philo->meal_lock);
    
    ft_message("is eating", philo, philo->id);
    ft_delay(philo->time_to_eat);
    
    pthread_mutex_lock(philo->meal_lock);
    philo->eating = 0;
    pthread_mutex_unlock(philo->meal_lock);
    
    // Release forks
    pthread_mutex_unlock(philo->l_fork);
    pthread_mutex_unlock(philo->r_fork);
}