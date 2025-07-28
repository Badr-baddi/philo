/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-bad <bael-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 10:21:19 by bael-bad          #+#    #+#             */
/*   Updated: 2025/07/27 23:32:13 by bael-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_monitor_thread(t_program *program)
{
	pthread_t	monitor;
	
	// Create the monitor thread, passing the program struct as argument
	if (pthread_create(&monitor, NULL, monitor_routine, program) != 0)
	{
		printf("Failed to create monitor thread\n");
		return (1);
	}
	
	// Detach the monitor thread so we don't need to join it explicitly
	// It will be cleaned up automatically when it exits
	if (pthread_detach(monitor) != 0)
	{
		printf("Failed to detach monitor thread\n");
		return (1);
	}
	
	return (0);
}

int	main(int ac, char **av)
{
	int			nbr;
	t_program	program;

	program.dead_flag = 0;
	if (ac < 5 || ac > 6)
	{
		printf("Usage: ./program nbr time1 time2 time3 [num_times_each_philo_must_eat]\n");
		return (1);
	}
	nbr = ft_atoi(av[1]);
	if (!parss_1(nbr, av, ac))
		return (1);
	if (!program.dead_flag)
		ft_init(&program, av);
	init_monitor_thread(&program);

}
