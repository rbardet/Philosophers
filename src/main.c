/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 22:43:07 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/01 23:00:55 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"


int	main(int argc, char **argv)
{
	t_rules				*rules;
	pthread_mutex_t		**fork;

	if (argc < 5 || argc > 6)
	{
		write(2, TOO_MANY_ARG, ft_strlen(TOO_MANY_ARG));
		return (1);
	}
	rules = init_rules(argc, argv);
	if (rules->check != 0)
		return (1);
	if (check_rules(rules) == 0)
	{
		write(2, NULL_ARG, ft_strlen(NULL_ARG));
		return (1);
	}
	fork = init_forks(rules->nb_philo);
	init_philo(fork, rules);
	create_thread(fork, rules);
	return (0);
}
