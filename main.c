/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-bad <bael-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 10:21:19 by bael-bad          #+#    #+#             */
/*   Updated: 2025/07/25 22:18:06 by bael-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	int			nbr;
	t_program	program;
	int			i;

	i = 0;
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
	{
		ft_init(&program, &av[1]);
	}
}
