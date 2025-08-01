/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-bad <bael-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 10:21:19 by bael-bad          #+#    #+#             */
/*   Updated: 2025/07/31 16:27:52 by bael-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	int		nbr;
	t_table	table;
	pthread_t	monitor_thread;

	if (ac < 5 || ac > 6)
	{
		printf("Usage: ./program nbr time1 time2 time3 [num_times_each_philo_must_eat]\n");
		return (1);
	}
	nbr = ft_atoi(av[1]);
	if (!parss_1(nbr, av, ac))
		return (1);
	if (init_mutexes(&table))
	{
		write(2, "Mutex init failed\n", 18);
		return (1);
	}
	init_tab1(&table, av);
	init_diners(&table);
	if (start_threads(&table))
	{
		write(2, "Creation failed\n", 17);
		return (1);
	}
	if (pthread_create(&monitor_thread, NULL, monitor, &table) != 0)
	{
		write(2, "Monitor failed\n", 16);
			return (1);
	}
	pthread_join(monitor_thread, NULL);
	join_threads(&table);
	destroy_mutexes(&table);
}
