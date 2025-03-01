/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 22:30:23 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/02 00:20:38 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_rules(t_rules *rules)
{
	if (rules->nb_philo < 0 || rules->time_to_die < 0
		|| rules->time_to_eat < 0 || rules->time_to_eat < 0
		|| rules->time_to_sleep < 0)
	{
		return (0);
	}
	else
		return (1);
}

t_rules	*is_valid_arg(char **argv)
{
	int		i;
	int		j;
	t_rules	*rules;

	i = 1;
	rules = malloc(sizeof(t_rules));
	if (!rules)
	{
		write(2, MALLOC_ERROR, ft_strlen(MALLOC_ERROR));
		return (NULL);
	}
	rules->check = 0;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
			{
				write(2, NON_NUMERIC_ARG, ft_strlen(NON_NUMERIC_ARG));
				rules->check++;
				return (rules);
			}
			j++;
		}
		i++;
	}
	return (rules);
}

t_rules	*init_rules(int argc, char **argv)
{
	t_rules *rules;

	rules = is_valid_arg(argv);
	rules->nb_philo = ft_atoi(argv[1]);
	if (rules->nb_philo > 200)
	{
		rules->check++;
		write(2, TOO_MANY_PHILO, ft_strlen(TOO_MANY_PHILO));
	}
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		rules->number_of_meal = ft_atoi(argv[5]);
		if (rules->number_of_meal < 0)
		{
			write(2, NULL_ARG, ft_strlen(NULL_ARG));
			rules->check++;
		}
	}
	else
		rules->number_of_meal = -1;
	return (rules);
}

void	init_philo(pthread_mutex_t **fork, t_rules *rules)
{
	int	i;

	i = 0;
	rules->philo = malloc(sizeof(t_philo) * (rules->nb_philo + 1));
	if (!rules->philo)
	{
		write(2, MALLOC_ERROR, ft_strlen(MALLOC_ERROR));
		exit (EXIT_FAILURE);
	}
	if (pthread_mutex_init(&rules->write_lock, NULL) != 0
		|| pthread_mutex_init(&rules->dead_lock, NULL) != 0)
	{
		write(2, MUTEX_ERROR, ft_strlen(MUTEX_ERROR));
		exit (EXIT_FAILURE);
	}
	while (i < rules->nb_philo)
	{
		rules->philo[i].id = i + 1;
		rules->philo[i].time_eaten = 0;
		rules->philo[i].write_lock = &rules->write_lock;
		rules->philo[i].dead_lock = &rules->dead_lock;
		rules->philo[i].left_fork = fork[i];
		if (i == 0)
			rules->philo[i].right_fork = fork[rules->nb_philo - 1];
		else
			rules->philo[i].right_fork = fork[i - 1];
		i++;
	}
}

pthread_mutex_t	**init_forks(int nb_philo)
{
	int				i;
	pthread_mutex_t **fork;

	fork = malloc(sizeof(pthread_mutex_t *) * (nb_philo + 1));
	i = 0;
	while (i < nb_philo)
	{
		fork[i] = malloc(sizeof(pthread_mutex_t));
		if (pthread_mutex_init(fork[i], NULL) != 0)
		{
			while(i != 0)
			{
				pthread_mutex_destroy(fork[i]);
				i--;
			}
			write(2, MUTEX_ERROR, ft_strlen(MUTEX_ERROR));
			exit (EXIT_FAILURE);
		}
		i++;
	}
	return (fork);
}
