/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_state.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 04:55:37 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/08 16:41:09 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	alive_state(t_philo *philo, t_rules *rules)
{
	sem_wait(philo->rules->state_lock);
	if (((get_timestamp() - philo->last_meal) > philo->rules->time_to_die))
	{
		sem_post(philo->rules->state_lock);
		free_all(rules);
		exit (EXIT_SUCCESS);
	}
	sem_post(philo->rules->state_lock);
	return (1);
}

void	print_status(t_philo *philo, char *status, t_rules *rules)
{
	sem_wait(philo->rules->write_lock);
	if (!alive_state(philo, rules) && ft_strcmp(status, "died"))
	{
		sem_post(philo->rules->write_lock);
		return ;
	}
	printf("%6lli " "%4d " "%s\n", get_timestamp() - philo->rules->start_time,
		philo->id, status);
	sem_post(philo->rules->write_lock);
}
