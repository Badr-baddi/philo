/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-bad <bael-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:49:29 by bael-bad          #+#    #+#             */
/*   Updated: 2025/08/03 17:26:14 by bael-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sign(int *s, long *i, const char *str)
{
	*s = 1;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			*s = -1;
		(*i)++;
	}
}

void	ft_space(long *i, const char *str)
{
	*i = 0;
	while (str[*i] == 32 || (str[*i] >= 9 && str[*i] <= 13))
		(*i)++;
}

int	ft_atoi(const char *str)
{
	long	i;
	long	t;
	long	oldt;
	int		s;

	t = 0;
	oldt = 0;
	ft_space(&i, str);
	ft_sign(&s, &i, str);
	while (str[i] >= '0' && str[i] <= '9')
	{
		t = (t * 10) + (str[i++] - '0');
		if ((t / 10) != oldt && s < 0)
			return (0);
		else if ((t / 10) != oldt && s > 0)
			return (-1);
		oldt = t;
	}
	return ((int)t * s);
}
