/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 22:30:23 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/08 15:59:47 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_rules	*is_valid_arg(char **argv)
{
	t_rules	*rules;

	rules = malloc(sizeof(t_rules));
	if (!rules)
	{
		write(2, MALLOC_ERROR, ft_strlen(MALLOC_ERROR));
		return (NULL);
	}
	rules->check = 0;
	rules = only_digit_arg(rules, argv);
	return (rules);
}

t_rules	*init_rules(int argc, char **argv)
{
	t_rules	*rules;

	rules = is_valid_arg(argv);
	rules->nb_philo = ft_atol(argv[1]);
	if (rules->nb_philo > 200)
	{
		rules->check++;
		write(2, "Do no test with more than 200 philo.\n", 38);
	}
	rules->time_to_die = ft_atol(argv[2]);
	rules->time_to_eat = ft_atol(argv[3]);
	rules->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
	{
		rules->number_of_meal = ft_atol(argv[5]);
		if (rules->number_of_meal < 0)
		{
			write(2, "At least on rule is not valid", 30);
			rules->check++;
		}
	}
	else
		rules->number_of_meal = -1;
	rules->start_time = get_timestamp();
	return (rules);
}

t_rules	*init_mutex(t_rules *rules)
{
	rules->philo = malloc(sizeof(t_philo) * (rules->nb_philo + 1));
	if (!rules->philo)
	{
		write(2, MALLOC_ERROR, ft_strlen(MALLOC_ERROR));
		return (NULL);
	}
	if (pthread_mutex_init(&rules->write_lock, NULL) != 0
		|| pthread_mutex_init(&rules->dead_lock, NULL) != 0
		|| pthread_mutex_init(&rules->state_lock, NULL) != 0)
	{
		write(2, "Error while initing a mutex\n", 29);
		return (NULL);
	}
	return (rules);
}

void	init_philo(pthread_mutex_t **fork, t_rules *rules)
{
	int	i;

	i = 0;
	rules = init_mutex(rules);
	if (!rules->philo)
		return ;
	while (i < rules->nb_philo)
	{
		rules->philo[i].is_dead = &rules->is_dead;
		rules->philo[i].first_dead = &rules->first_dead;
		rules->philo[i].id = i + 1;
		rules->philo[i].time_eaten = 0;
		rules->philo[i].last_meal = get_timestamp();
		rules->philo[i].left_fork = fork[i];
		if (i == 0)
			rules->philo[i].right_fork = fork[rules->nb_philo - 1];
		else
			rules->philo[i].right_fork = fork[i - 1];
		rules->philo[i].rules = rules;
		i++;
	}
}

pthread_mutex_t	**init_forks(int nb_philo)
{
	int				i;
	pthread_mutex_t	**fork;

	fork = malloc(sizeof(pthread_mutex_t *) * (nb_philo + 1));
	i = 0;
	while (i < nb_philo)
	{
		fork[i] = malloc(sizeof(pthread_mutex_t));
		if (pthread_mutex_init(fork[i], NULL) != 0)
		{
			while (i != 0)
			{
				pthread_mutex_destroy(fork[i]);
				i--;
			}
			write(2, "Error while initing a mutex\n", 29);
			return (NULL);
		}
		i++;
	}
	return (fork);
}
