/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 03:12:39 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/08 16:42:22 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	eating(t_philo *philo, t_rules *rules)
{
	sem_wait(philo->rules->fork);
	print_status(philo, "has taken a fork", rules);
	if (philo->rules->nb_philo == 1)
	{
		sem_post(philo->rules->fork);
		return ;
	}
	sem_wait(philo->rules->fork);
	print_status(philo, "has taken a fork", rules);
	print_status(philo, "is eating", rules);
	sem_wait(philo->rules->state_lock);
	philo->last_meal = get_timestamp();
	sem_post(philo->rules->state_lock);
	philo->time_eaten++;
	better_usleep(philo->rules->time_to_eat, philo, rules);
	sem_post(philo->rules->fork);
	sem_post(philo->rules->fork);
}

void	philo_routine(t_philo *philo, t_rules *rules)
{
	if (philo->id % 2 == 0)
		usleep(500);
	while (alive_state(philo, rules))
	{
		eating(philo, rules);
		if (philo->rules->nb_philo == 1)
		{
			usleep(philo->rules->time_to_die * 1000);
			break ;
		}
		if (philo->time_eaten == philo->rules->number_of_meal)
		{
			free_all(rules);
			exit (FULL);
		}
		print_status(philo, "is sleeping", rules);
		better_usleep(philo->rules->time_to_sleep, philo, rules);
		print_status(philo, "is thinking", rules);
		usleep(500);
	}
	free_all(rules);
	exit (EXIT_SUCCESS);
}

void	end_process(t_rules *rules, pid_t death_check)
{
	int	i;

	i = 0;
	while (i < rules->nb_philo)
	{
		if (rules->wait_philo[i] != death_check)
			kill(rules->wait_philo[i], SIGTERM);
		if (rules->wait_philo[i] == death_check)
		{
			printf("%6lli " "%4d " "is dead\n", get_timestamp()
				- rules->start_time, i + 1);
		}
		i++;
	}
	i = 0;
	while (i < rules->nb_philo)
	{
		waitpid(rules->wait_philo[i], NULL, 0);
		i++;
	}
}

void	wait_till_end(t_rules *rules)
{
	pid_t	death_check;
	int		i;
	int		status;

	i = 0;
	while (1)
	{
		death_check = waitpid(-1, &status, 0);
		if ((status > 0))
			i++;
		if (!(WIFEXITED(status) && WEXITSTATUS(status) == FULL))
			break ;
		if (i == rules->nb_philo)
			return ;
	}
	if (death_check > 0 && status != FULL)
		end_process(rules, death_check);
}

void	create_philo(t_rules *rules)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < rules->nb_philo)
	{
		pid = fork();
		if (pid == -1)
			exit (exit_print("Fork error"));
		if (pid == 0)
			philo_routine(&rules->philo[i], rules);
		rules->wait_philo[i] = pid;
		i++;
	}
	wait_till_end(rules);
}
