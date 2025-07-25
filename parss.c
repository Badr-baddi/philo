/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parss.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-bad <bael-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 11:45:04 by bael-bad          #+#    #+#             */
/*   Updated: 2025/07/17 13:30:04 by bael-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int parss(char *av)
{
    int i = 0;

    while (av[i])
    {
        if (av[i] < '0' || av[i] > '9')
        {
            printf("THE INPUT IS NOT CORRECT :(\n");
            return 0;
        }
        i++;
    }
    printf("THE INPUT IS TRUE :)\n");
    printf("%s\n", av);
    return 1;
}
