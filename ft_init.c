/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-bad <bael-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 21:55:19 by bael-bad          #+#    #+#             */
/*   Updated: 2025/07/27 23:47:36 by bael-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routin_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (1)
	{
		pthread_mutex_lock(&philo->program->dead_lock);
		if (philo->program->dead_flag)
		{
			pthread_mutex_unlock(&philo->program->dead_lock);
			break;
		}
		pthread_mutex_unlock(&philo->program->dead_lock);
		ft_eat(philo);
		if (philo->num_times_to_eat != -1 &&
			philo->meals_eaten >= philo->num_times_to_eat)
				break;
		if (philo->program->dead_flag)
		{
			pthread_mutex_unlock(&philo->program->dead_lock);
			break;
		}
		ft_sleep(philo);
		if (philo->program->dead_flag)
		{
			pthread_mutex_unlock(&philo->program->dead_lock);
			break;
		}
		ft_think(philo);
	}
	return NULL;
}

size_t get_time(void)
{
    struct timeval time;

    if (gettimeofday(&time, NULL) == -1)
        write(2, "gettimeofday() error\n", 22);
    // Convert seconds to milliseconds and microseconds to milliseconds
    return (time.tv_sec * 1000) + (time.tv_usec / 1000);
}

void    ft_init1(t_program *program, char **av, int num_of_philo, t_philo *philos)
{
	size_t          start_time;
	pthread_mutex_t	forks[MAX_PHILOS];
	int             i;

	i = 0;
	start_time = get_time();

	while (i < num_of_philo)
	{
		philos[i].id = i + 1;
		philos[i].program = program;
		philos[i].num_of_philos = num_of_philo;
		philos[i].start_time = start_time;
		philos[i].last_meal = start_time;
		philos[i].meals_eaten = 0;
		philos[i].eating = 0;
		philos[i].time_to_die = ft_atoi(av[2]);
		philos[i].time_to_eat = ft_atoi(av[3]);
		philos[i].time_to_sleep = ft_atoi(av[4]);
		if (av[5])
			philos[i].num_times_to_eat = ft_atoi(av[5]);
		else
			philos[i].num_times_to_eat = -1;
		philos[i].l_fork = &forks[i];
		philos[i].r_fork = &forks[(i + 1) % num_of_philo];
		philos[i].write_lock = &program->write_lock;
		philos[i].meal_lock = &program->meal_lock;
		philos[i].dead_lock = &program->dead_lock;
		philos[i].dead = &program->dead_flag;
		i++;
	}
}


// void ft_init(t_program *program, char **arg)
// {
//     int i;
// 	pthread_t	monitor;
//     i = 0;
//     program->dead_flag = 0;
//     program->num_of_philo = ft_atoi(arg[1]);
//     pthread_mutex_init(&program->write_lock, NULL);
//     pthread_mutex_init(&program->meal_lock, NULL);
//     pthread_mutex_init(&program->dead_lock, NULL);
//     while (i < program->num_of_philo)
//     {
//         pthread_mutex_init(&program->forks[i], NULL);
//         i++;
//     }
//     ft_init1(program, arg, program->num_of_philo, program->philos);
//     i = 0;
//     while (i < program->num_of_philo)
//     {
//         pthread_create(&program->philos[i].thread, NULL, routin_philo, &program->philos[i]);
//         i++;
//     }
//     pthread_create(&monitor, NULL, monitor_routine, program);
//     pthread_join(monitor, NULL);
//     i = 0;
//     while (i < program->num_of_philo)
//     {
//         pthread_join(program->philos[i].thread, NULL);
//         i++;
//     }
// }

void ft_init(t_program *program, char **arg)
{
    int i;
    
    i = 0;
    program->dead_flag = 0;
    program->num_of_philo = ft_atoi(arg[1]);
    
    // Initialize mutexes
    pthread_mutex_init(&program->write_lock, NULL);
    pthread_mutex_init(&program->meal_lock, NULL);
    pthread_mutex_init(&program->dead_lock, NULL);
    
    // Initialize fork mutexes
    while (i < program->num_of_philo)
    {
        pthread_mutex_init(&program->forks[i], NULL);
        i++;
    }
    
    // Initialize philosophers
    ft_init1(program, arg, program->num_of_philo, program->philos);
    
    // Create philosopher threads
    i = 0;
    while (i < program->num_of_philo)
    {
        pthread_create(&program->philos[i].thread, NULL, routin_philo, &program->philos[i]);
        i++;
    }
    
    // Create and detach monitor thread
    init_monitor_thread(program);
    
    // Wait for philosopher threads to finish
    i = 0;
    while (i < program->num_of_philo)
    {
        pthread_join(program->philos[i].thread, NULL);
        i++;
    }
    
    // Clean up mutexes
    pthread_mutex_destroy(&program->write_lock);
    pthread_mutex_destroy(&program->meal_lock);
    pthread_mutex_destroy(&program->dead_lock);
    
    i = 0;
    while (i < program->num_of_philo)
    {
        pthread_mutex_destroy(&program->forks[i]);
        i++;
    }
}