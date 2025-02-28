/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 22:43:07 by rbardet-          #+#    #+#             */
/*   Updated: 2025/02/28 23:21:03 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	do_rules(t_rules rules)
{
	printf("Philo : %d\n", rules.init_philo);
}


int	main(int argc, char **argv)
{
	t_rules		rules;
	pthread_t	*philo;

	if (argc < 5 || argc > 6)
	{
		write(2, TOO_MANY_ARG, ft_strlen(TOO_MANY_ARG));
		return (1);
	}
	rules = init_rules(argc, argv);
	if (rules.check != 0)
		return (1);
	if (check_rules(rules) == 0)
	{
		write(2, NULL_ARG, ft_strlen(NULL_ARG));
		return (1);
	}
	philo = malloc(sizeof(t_rules) * (rules.nb_philo));
	while (rules.init_philo < rules.nb_philo)
	{
		if (pthread_create(&philo[rules.init_philo], NULL, (void *)do_rules, &rules) == -1)
			return(1);
		rules.init_philo++;
	}
	while (rules.init_philo != 0)
	{
		pthread_join(philo[rules.init_philo], NULL);
		rules.init_philo--;
	}
	free (philo);
	return (0);
}
