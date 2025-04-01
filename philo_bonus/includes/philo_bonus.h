/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 04:21:04 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/08 15:37:26 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>

# define MALLOC_ERROR "Error with a malloc\n"
# define FULL 3

typedef struct s_rules
{
	int					nb_philo;
	long long			time_to_die;
	long long			time_to_eat;
	long long			time_to_sleep;
	int					number_of_meal;
	int					check;
	long long			start_time;
	sem_t				*write_lock;
	sem_t				*dead_lock;
	sem_t				*state_lock;
	sem_t				*fork;
	pid_t				*wait_philo;
	struct s_philo		*philo;
}						t_rules;

typedef struct s_philo
{
	pthread_t			thread;
	int					id;
	int					time_eaten;
	int					nb_philo;
	long long			last_meal;
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
t_rules			*init_semaphore(t_rules *rules);
int				exit_print(char *message);
void			init_philo(t_rules *rules);
sem_t			*init_forks(int nb_philo);
void			free_all(t_rules *rules);
void			create_philo(t_rules *rules);
void			philo_routine(t_philo *philo, t_rules *rules);
void			end_process(t_rules *rules, pid_t death_check);
long long		get_timestamp(void);
void			better_usleep(long long time, t_philo *philo, t_rules *rules);
void			eating(t_philo *philo, t_rules *rules);
void			print_status(t_philo *philo, char *status, t_rules *rules);
int				alive_state(t_philo *philo, t_rules *rules);
int				exit_print(char *message);
void			wait_till_end(t_rules *rules);

#endif
