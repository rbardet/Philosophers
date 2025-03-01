/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 03:12:39 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/02 00:22:47 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	free_prog(pthread_mutex_t **fork, t_rules *rules)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&rules->write_lock);
	pthread_mutex_destroy(&rules->dead_lock);
	while (i < rules->nb_philo)
	{
		pthread_mutex_destroy(fork[i]);
		free(fork[i]);
		i++;
	}
	free(rules->philo);
	free(rules);
	free(fork);
}

void	philo_routine(t_philo *philo)
{
	pthread_mutex_lock(philo->write_lock);
	pthread_mutex_lock(philo->left_fork);
	printf("%d " TAKEN_FORK, philo->id);
	pthread_mutex_unlock(philo->write_lock);
	pthread_mutex_lock(philo->write_lock);
	pthread_mutex_lock(philo->right_fork);
	printf("%d " TAKEN_FORK, philo->id);
	pthread_mutex_unlock(philo->write_lock);
	pthread_mutex_lock(philo->write_lock);
	printf("%d " IS_EATING, philo->id);
	pthread_mutex_unlock(philo->write_lock);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_lock(philo->write_lock);
	printf("%d " IS_SLEEPING, philo->id);
	pthread_mutex_unlock(philo->write_lock);
	pthread_mutex_lock(philo->write_lock);
	printf("%d " IS_THINKING, philo->id);
	pthread_mutex_unlock(philo->write_lock);
}

void	create_thread(pthread_mutex_t **fork, t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->nb_philo)
	{
		if (pthread_create(&rules->philo[i].thread, NULL, (void *)philo_routine, &rules->philo[i]) != 0)
		{
			free_prog(fork, rules);
			write(2, THREAD_ERROR, ft_strlen(THREAD_ERROR));
			exit (EXIT_FAILURE);
		}
		i++;
	}
	while (i != 0)
	{
		pthread_join(rules->philo[i].thread, NULL);
		i--;
	}
	free_prog(fork, rules);
}
