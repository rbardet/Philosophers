/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 04:21:04 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/08 16:11:07 by rbardet-         ###   ########.fr       */
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

# define MALLOC_ERROR "Error with a malloc\n"

typedef struct s_rules
{
	int					nb_philo;
	long long			time_to_die;
	long long			time_to_eat;
	long long			time_to_sleep;
	int					number_of_meal;
	int					check;
	int					is_dead;
	int					first_dead;
	long long			start_time;
	pthread_mutex_t		write_lock;
	pthread_mutex_t		dead_lock;
	pthread_mutex_t		state_lock;
	struct s_philo		*philo;
}						t_rules;

typedef struct s_philo
{
	pthread_t			thread;
	int					id;
	int					time_eaten;
	int					nb_philo;
	long long			last_meal;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	int					*is_dead;
	int					*first_dead;
	struct s_rules		*rules;
}						t_philo;

long long		ft_atol(const char *nptr);
int				ft_isdigit(int c);
size_t			ft_strlen(const char *s);
int				ft_strcmp(char *s1, char *s2);

t_rules			*init_rules(int argc, char **argv);
int				check_rules(t_rules *rules);
t_rules			*only_digit_arg(t_rules *rules, char **argv);
t_rules			*is_valid_arg(char **argv);
t_rules			*init_mutex(t_rules *rules);
void			init_philo(pthread_mutex_t **fork, t_rules *rules);
pthread_mutex_t	**init_forks(int nb_philo);
void			free_all(pthread_mutex_t **fork, t_rules *rules);
void			create_thread(pthread_mutex_t **fork, t_rules *rules);
void			philo_routine(t_philo *philo);
long long		get_timestamp(void);
void			eating(t_philo *philo);
void			print_status(t_philo *philo, char *status);
void			better_usleep(long long time, t_philo *philo);
int				all_alive(t_philo *philo);
int				alive_state(t_philo *philo);
t_rules			*get_rules(int argc, char **argv);
int				end_of_prog(t_philo *philo);

#endif
