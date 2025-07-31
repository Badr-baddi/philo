/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-bad <bael-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 10:22:52 by bael-bad          #+#    #+#             */
/*   Updated: 2025/07/31 15:51:49 by bael-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <limits.h>
#include <sys/time.h>

#define MAX_DINERS 200

typedef struct s_table t_table;

typedef struct s_diner
{	
	int         id;
	int         meals_eaten;
	size_t   last_meal_time;
	pthread_t   thread;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	t_table     *table;
}	t_diner;

typedef struct s_table
{
	int             total_diners;
	size_t          time_to_die;
	int             time_to_eat;
	int             time_to_sleep;
	int             must_eat;
	long long       start_time;
	pthread_mutex_t forks[MAX_DINERS];
	pthread_mutex_t print_lock;
	pthread_mutex_t death_lock;
	int             someone_died;
	t_diner         diners[MAX_DINERS];
} t_table;

int 	main(int ac, char **av);
int		parss(char *av);
int		ft_atoi(const char *str);
int 	parss_1(int nbr, char **av, int ac);
int	ft_usleep(size_t milliseconds);
int	ft_strcmp(char *s1, char *s2);
size_t	get_current_time(void);
int init_mutexes(t_table *table);
void    init_diners(t_table *table);
void init_tab1(t_table *table, char **av);
void	*routine(void *arg);
int	start_threads(t_table *table);
void	join_threads(t_table *table);
void	*monitor(void *arg);
void	destroy_mutexes(t_table *table);
int	check_death(t_table *table);

#endif