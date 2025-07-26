/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-bad <bael-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 21:55:19 by bael-bad          #+#    #+#             */
/*   Updated: 2025/07/26 22:54:35 by bael-bad         ###   ########.fr       */
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
		// if (is_dead(philo))
		// 	break;
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return NULL;
}

size_t  get_time(void)
{
	struct timeval  time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_sec / 1000);
}
void    ft_init1(t_program *program, char **av, int num_of_philo, t_philo philos[MAX_PHILOS])
{
	size_t          start_time;
	pthread_mutex_t	forks[MAX_PHILOS];
	int             i;

	i = 0;
	start_time = get_time();

	while (i < num_of_philo)
	{
		philos[i].id = i + 1;
		printf("%d\n", philos[i].id);
		philos[i].num_of_philos = num_of_philo;
		// printf("%d\n", philos[i].num_of_philos);
		philos[i].start_time = start_time;
		philos[i].last_meal = start_time;
		philos[i].meals_eaten = 0;
		philos[i].eating = 0;
		philos[i].time_to_die = ft_atoi(av[0]);
		philos[i].time_to_eat = ft_atoi(av[1]);
		philos[i].time_to_sleep = ft_atoi(av[2]);
		if (av[3])
			philos[i].num_times_to_eat = ft_atoi(av[3]);
		philos[i].l_fork = &forks[i];
		philos[i].r_fork = &forks[(i + 1) % num_of_philo];
		philos[i].write_lock = &program->write_lock;
		philos[i].meal_lock = &program->meal_lock;
		philos[i].dead_lock = &program->dead_lock;
		philos[i].dead = &program->dead_flag;
		i++;
	}
	//exit(1);
}

void    ft_init(t_program *program, char **arg)
{
	int          i;
	t_philo	        philos[MAX_PHILOS];

	i = 0;
	program->dead_flag = 0;
	program->num_of_philo = ft_atoi(arg[0]);
	pthread_mutex_init(&program->write_lock, NULL);
	pthread_mutex_init(&program->meal_lock, NULL);
	pthread_mutex_init(&program->dead_lock, NULL);
	while (i < program->num_of_philo)
	{
		pthread_mutex_init(&program->forks[i], NULL);
		i++;
	}
	ft_init1(program, arg, program->num_of_philo, philos);
	i = 0;
	while (i < program->num_of_philo)
	{
		pthread_create(&philos[i].thread, NULL, routin_philo, &philos[i]);
	}
}
