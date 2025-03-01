/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 04:21:04 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/02 00:52:27 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

# define TOO_MANY_ARG "Wrong number of argument.\n"
# define NULL_ARG "At least one rule is not valid.\n"
# define NON_NUMERIC_ARG "One argument contain non numeric parameter.\n"
# define TOO_MANY_PHILO "Do no test with more than 200 philo.\n"
# define MUTEX_ERROR "Error while initing a mutex\n"
# define THREAD_ERROR "Error while initing philo thread\n"
# define MALLOC_ERROR "Error with a malloc\n"
# define TAKEN_FORK "has taken a fork\n"
# define IS_EATING "is eating\n"
# define IS_SLEEPING "is sleeping\n"
# define IS_THINKING "is thinking\n"
# define DIED "died\n"

typedef struct t_philo
{
	pthread_t			thread;
	int					id;
	int					time_eaten;
	int					last_meal;
	pthread_mutex_t		*write_lock;
	pthread_mutex_t		*dead_lock;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
}						t_philo;

typedef struct t_rules
{
	int					nb_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_of_meal;
	int					check;
	int					current_time;
	pthread_mutex_t		write_lock;
	pthread_mutex_t		dead_lock;
	t_philo				*philo;
}						t_rules;

int		ft_atoi(const char *nptr);
int		ft_isdigit(int c);
size_t	ft_strlen(const char *s);

t_rules			*init_rules(int argc, char **argv);
int				check_rules(t_rules *rules);
t_rules			*is_valid_arg(char **argv);
void			init_philo(pthread_mutex_t **fork, t_rules *rules);
pthread_mutex_t	**init_forks(int nb_philo);
void			free_prog(pthread_mutex_t **fork, t_rules *rules);
void			create_thread(pthread_mutex_t **fork, t_rules *rules);
void			philo_routine(t_philo *philo);

#endif
