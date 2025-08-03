/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parss_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-bad <bael-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:30:33 by bael-bad          #+#    #+#             */
/*   Updated: 2025/08/03 17:23:46 by bael-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parss_1(int nbr, char **av, int ac)
{
	int	i;

	i = 0;
	if (nbr > 200
		|| nbr <= 0
		|| ft_atoi(av[2]) < 60
		|| ft_atoi(av[3]) < 60
		|| ft_atoi(av[4]) < 60
		|| (av[5] && ft_atoi(av[5]) <= 0))
	{
		printf("Condition met: skipping parsing.\n");
		return (0);
	}
	i = 1;
	while (i < ac)
	{
		if (!parss(av[i]))
		{
			printf("Condition met: skipping parsing.\n");
			return (0);
		}
		i++;
	}
	return (1);
}
