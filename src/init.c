/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 22:30:23 by rbardet-          #+#    #+#             */
/*   Updated: 2025/02/28 23:01:23 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_rules(t_rules rules)
{
	if (rules.nb_philo == 0 || rules.time_to_die == 0
		|| rules.time_to_eat == 0 || rules.time_to_eat == 0
		|| rules.time_to_sleep == 0 || rules.number_of_meal == 0)
	{
		return (0);
	}
	else
		return (1);
}

t_rules	is_valid_arg(char **argv)
{
	int		i;
	int		j;
	t_rules	rules;

	i = 1;
	rules.check = 0;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
			{
				write(2, NON_NUMERIC_ARG, ft_strlen(NON_NUMERIC_ARG));
				rules.check++;
				return (rules);
			}
			j++;
		}
		i++;
	}
	return (rules);
}

t_rules	init_rules(int argc, char **argv)
{
	t_rules rules;

	rules.check = 0;
	rules = is_valid_arg(argv);
	rules.init_philo = 0;
	rules.nb_philo = ft_atoi(argv[1]);
	if (rules.nb_philo > 200)
	{
		rules.check++;
		write(2, TOO_MANY_PHILO, ft_strlen(TOO_MANY_PHILO));
	}
	rules.time_to_die = ft_atoi(argv[2]);
	rules.time_to_eat = ft_atoi(argv[3]);
	rules.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		rules.number_of_meal = ft_atoi(argv[5]);
	else
		rules.number_of_meal = -1;
	return (rules);
}

