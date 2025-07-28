/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-bad <bael-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 10:22:52 by bael-bad          #+#    #+#             */
/*   Updated: 2025/07/27 23:34:32 by bael-bad         ###   ########.fr       */
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

#define MAX_PHILOS 200

// typedef struct s_program
// {
// 	int				dead_flag;
// 	pthread_mutex_t	dead_lock;
// 	pthread_mutex_t	meal_lock;
// 	pthread_mutex_t	write_lock;
// 	pthread_mutex_t forks[MAX_PHILOS];
// 	int             num_of_philo;
// }	t_program;

typedef struct s_program t_program;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				num_of_philos;
	int				num_times_to_eat;
	int				*dead;
	pthread_mutex_t philos[MAX_PHILOS];
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
	t_program		*program;  // ✅ now shared properly
}	t_philo;

typedef struct s_program
{
    int dead_flag;
    pthread_mutex_t dead_lock;
    pthread_mutex_t meal_lock;
    pthread_mutex_t write_lock;
    pthread_mutex_t forks[MAX_PHILOS];
    int num_of_philo;
    t_philo philos[MAX_PHILOS];  // Add philosophers here
} t_program;







int 	main(int ac, char **av);
int		parss(char *av);
int		ft_atoi(const char *str);
int 	parss_1(int nbr, char **av, int ac);
void    ft_init(t_program *program, char **arg);
void    ft_init1(t_program *program, char **av, int num_of_philo, t_philo *philos);
int	ft_usleep(size_t milliseconds);
void ft_message(char *msg, t_philo *philo, int id);
int	is_dead(t_philo *philo);
int	ft_strcmp(char *s1, char *s2);
size_t  get_time(void);
void    ft_think(t_philo *philo);
void ft_eat(t_philo *philo);
void    ft_sleep(t_philo *philo);
void	ft_delay(size_t time_in_ms);
void	*routin_philo(void *arg);
void *monitor_routine(void *arg);
int	init_monitor_thread(t_program *program);

#endif