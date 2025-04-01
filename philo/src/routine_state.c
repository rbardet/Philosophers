/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_state.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 04:55:37 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/08 16:11:44 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	all_alive(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->state_lock);
	if (*philo->is_dead == 1)
	{
		pthread_mutex_unlock(&philo->rules->state_lock);
		return (0);
	}
	else
	{
		pthread_mutex_unlock(&philo->rules->state_lock);
		return (1);
	}
}

int	alive_state(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->state_lock);
	if (((get_timestamp() - philo->last_meal) > philo->rules->time_to_die))
	{
		*philo->is_dead = 1;
		pthread_mutex_unlock(&philo->rules->state_lock);
		return (0);
	}
	pthread_mutex_unlock(&philo->rules->state_lock);
	return (1);
}

int	end_of_prog(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->dead_lock);
	if (*philo->first_dead == 1)
	{
		pthread_mutex_unlock(&philo->rules->dead_lock);
		return (1);
	}
	*philo->first_dead = 1;
	pthread_mutex_unlock(&philo->rules->dead_lock);
	print_status(philo, "died");
	return (0);
}
