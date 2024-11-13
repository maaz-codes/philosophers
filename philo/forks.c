/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:15:20 by maakhan           #+#    #+#             */
/*   Updated: 2024/11/09 12:39:19 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	forks_available(t_philo *philo)
{
	int	own_fork;
	int	other_fork;

	pthread_mutex_lock(&philo->info->f_register_locks[philo->own_fork]);
	own_fork = philo->info->forks[philo->own_fork];
	pthread_mutex_unlock(&philo->info->f_register_locks[philo->own_fork]);
	pthread_mutex_lock(&philo->info->f_register_locks[philo->other_fork]);
	other_fork = philo->info->forks[philo->other_fork];
	pthread_mutex_unlock(&philo->info->f_register_locks[philo->other_fork]);
	if (own_fork == -1 && other_fork == -1)
		return (TRUE);
	return (FALSE);
}

void	register_forks(t_philo *philo)
{
	mutex_lock(&philo->info->f_register_locks[philo->own_fork],
		&philo->info->forks[philo->own_fork], philo->id);
	mutex_lock(&philo->info->f_register_locks[philo->other_fork],
		&philo->info->forks[philo->other_fork], philo->id);
}

void	deregister_forks(t_philo *philo)
{
	mutex_lock(&philo->info->f_register_locks[philo->own_fork],
		&philo->info->forks[philo->own_fork], -1);
	mutex_lock(&philo->info->f_register_locks[philo->other_fork],
		&philo->info->forks[philo->other_fork], -1);
}

void	grab_forks(t_philo *philo)
{
	if (philo->own_fork < philo->other_fork)
	{
		pthread_mutex_lock(&philo->info->fork_locks[philo->own_fork]);
		pthread_mutex_lock(&philo->info->fork_locks[philo->other_fork]);
	}
	else
	{
		pthread_mutex_lock(&philo->info->fork_locks[philo->other_fork]);
		pthread_mutex_lock(&philo->info->fork_locks[philo->own_fork]);
	}
	write_lock(philo->info, philo, " has taken a fork");
	write_lock(philo->info, philo, " has taken a fork");
}

void	release_forks(t_philo *philo)
{
	if (philo->own_fork > philo->other_fork)
	{
		pthread_mutex_unlock(&philo->info->fork_locks[philo->own_fork]);
		pthread_mutex_unlock(&philo->info->fork_locks[philo->other_fork]);
	}
	else
	{
		pthread_mutex_unlock(&philo->info->fork_locks[philo->other_fork]);
		pthread_mutex_unlock(&philo->info->fork_locks[philo->own_fork]);
	}
}
