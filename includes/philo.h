/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 04:21:04 by rbardet-          #+#    #+#             */
/*   Updated: 2025/02/28 23:16:53 by rbardet-         ###   ########.fr       */
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

typedef struct t_rules
{
	int			nb_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			number_of_meal;
	int			check;
	int			init_philo;
}			t_rules;

int		ft_atoi(const char *nptr);
int		ft_isdigit(int c);
size_t	ft_strlen(const char *s);

t_rules	init_rules(int argc, char **argv);
int		check_rules(t_rules rules);
t_rules	is_valid_arg(char **argv);

void	do_rules(t_rules rules);

#endif
