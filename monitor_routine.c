// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   monitor_routine.c                                  :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: bael-bad <bael-bad@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/07/27 16:33:37 by bael-bad          #+#    #+#             */
// /*   Updated: 2025/07/27 23:16:53 by bael-bad         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "philo.h"

// int all_philos_ate_enough(t_philo *philos)
// {
// 	// (void)philos;
// 	// printf("all; %d\n", philos[0].num_of_philos);
// 	int i = 0;

// 	while (i < philos[0].num_of_philos)
// 	{
		
// 		// printf("meals: |%p| \t\t num: |%p|\n", &philos[i].meals_eaten, &philos[i].num_times_to_eat);
// 		// printf("lock: %p\n", &philos[i].meal_lock);
// 		// pthread_mutex_lock(philos[i].meal_lock);
// 		if (philos[i].meals_eaten < philos[i].num_times_to_eat)
// 		{
// 			// pthread_mutex_unlock(philos[i].meal_lock);
// 			return (0);
// 		}
// 		// pthread_mutex_unlock(philos[i].meal_lock);
// 		i++;
// 	}
// 	return (1);
// }



// void *monitor_routine(void *arg)
// {
// 	(void)arg;
// 	t_philo *philos = (t_philo *)arg;
// 	t_program *program = philos[0].program;
// 	int i;

// 	// printf("philo: %p", &philos[0].program);

// 	while (1)
// 	{
// 		i = 0;
// 		while (i < program->num_of_philo)
// 		{
// 			if (is_dead(&philos[i]))
// 				return (NULL);
// 			i++;
// 		}
// 		// printf("time: |%d|\n", philos[0].num_times_to_eat);
// 		// printf("%p\n", &philos);
// 		if (philos[0].num_times_to_eat != -1 && all_philos_ate_enough(philos))
// 		{
// 			// pthread_mutex_lock(&program->dead_lock);
// 			program->dead_flag = 1;
// 			// pthread_mutex_unlock(&program->dead_lock);
// 			return (NULL);
// 		}
// 		usleep(1000);
// 	}
// 	return (NULL);
// }

#include "philo.h"

/**
 * Checks if all philosophers have eaten enough meals
 * @param program The program struct containing all philosophers
 * @return 1 if all philosophers have eaten enough, 0 otherwise
 */
static int	check_meals_eaten(t_program *program)
{
	int	i;
	int	all_eaten;

	// If num_times_to_eat is not set (equals -1), return 0
	if (program->philos[0].num_times_to_eat == -1)
		return (0);
	
	i = 0;
	all_eaten = 1;
	
	pthread_mutex_lock(&program->meal_lock);
	while (i < program->num_of_philo)
	{
		if (program->philos[i].meals_eaten < program->philos[i].num_times_to_eat)
		{
			all_eaten = 0;
			break;
		}
		i++;
	}
	pthread_mutex_unlock(&program->meal_lock);
	
	return (all_eaten);
}

/**
 * Checks if any philosopher has died
 * @param program The program struct containing all philosophers
 * @return 1 if a philosopher has died, 0 otherwise
 */
static int	check_death(t_program *program)
{
	int		i;
	size_t	current_time;
	
	i = 0;
	while (i < program->num_of_philo)
	{
		current_time = get_time();
		pthread_mutex_lock(&program->meal_lock);
		if ((current_time - program->philos[i].last_meal) > 
			program->philos[i].time_to_die)
		{
			pthread_mutex_unlock(&program->meal_lock);
			pthread_mutex_lock(&program->dead_lock);
			program->dead_flag = 1;
			pthread_mutex_unlock(&program->dead_lock);
			ft_message("died", &program->philos[i], program->philos[i].id);
			return (1);
		}
		pthread_mutex_unlock(&program->meal_lock);
		i++;
	}
	return (0);
}

/**
 * Monitor routine that checks if philosophers are alive and if they've eaten enough
 * @param arg Pointer to t_program struct
 * @return NULL
 */
void	*monitor_routine(void *arg)
{
	t_program	*program;

	program = (t_program *)arg;
	
	// Small delay to let philosophers start eating
	ft_usleep(5);
	
	while (1)
	{
		if (check_death(program))
			break;
		if (check_meals_eaten(program))
		{
			pthread_mutex_lock(&program->dead_lock);
			program->dead_flag = 1;
			pthread_mutex_unlock(&program->dead_lock);
			break;
		}
		usleep(300);
	}
	return (NULL);
}