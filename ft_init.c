/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-bad <bael-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 21:55:19 by bael-bad          #+#    #+#             */
/*   Updated: 2025/07/25 22:38:51 by bael-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	routin()
{
	
}

size_t  get_time(void)
{
	struct timeval  time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_sec / 1000);
}
void    ft_init1(t_program *program, char **av, int num_of_philo)
{
	size_t          start_time;
	pthread_mutex_t	forks[MAX_PHILOS];
	t_philo	        philos[MAX_PHILOS];
	int             i;

	i = 0;
	start_time = get_time();

	while (i < num_of_philo)
	{
		philos[i].id = i + 1;
		philos[i].num_of_philos = num_of_philo;
		philos[i].start_time = start_time;
		philos[i].last_meal = start_time;
		philos[i].meals_eaten = 0;
		philos[i].eating = 0;
		philos[i].time_to_die = ft_atoi(av[1]);
		philos[i].time_to_eat = ft_atoi(av[2]);
		philos[i].time_to_sleep = ft_atoi(av[3]);
		if (av[4])
			philos[i].num_times_to_eat = ft_atoi(av[5]);
		philos[i].l_fork = &forks[i];
		philos[i].r_fork = &forks[(i + 1) % num_of_philo];
		philos[i].write_lock = &program->write_lock;
		philos[i].meal_lock = &program->meal_lock;
		philos[i].dead_lock = &program->dead_lock;
		philos[i].dead = &program->dead_flag;
		i++;
	}
}

void    ft_init(t_program *program, char **arg)
{
	t_program	*program;
	int          i;
	t_philo	        philos[MAX_PHILOS];

	i = 0;
	program->dead_flag = 0;
	program->num_of_philo = ft_atoi(arg[1]);
	pthread_mutex_init(&program->write_lock, NULL);
	pthread_mutex_init(&program->meal_lock, NULL);
	pthread_mutex_init(&program->dead_lock, NULL);
	while (i < program->num_of_philo)
	{
		pthread_mutex_init(&program->forks[i], NULL);
		i++;
	}
	ft_init1(program, arg, program->num_of_philo);
	i = 0;
	while (i < program->num_of_philo)
	{
		pthread_create(&philos[i].thread, NULL, );
	}
}
