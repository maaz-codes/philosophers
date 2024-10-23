/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinning_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 14:25:48 by maakhan           #+#    #+#             */
/*   Updated: 2024/10/23 21:02:39 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	forks_available(t_philo *philo)
{
	int	own_fork;
	int	other_fork;

	own_fork = 0;
	other_fork = 0;
	pthread_mutex_lock(&philo->info->fork_locks[philo->own_fork]);
	own_fork = philo->info->forks[philo->own_fork];
	pthread_mutex_unlock(&philo->info->fork_locks[philo->own_fork]);
	pthread_mutex_lock(&philo->info->fork_locks[philo->other_fork]);
	other_fork = philo->info->forks[philo->other_fork];
	pthread_mutex_unlock(&philo->info->fork_locks[philo->other_fork]);
	return (own_fork == 0 && other_fork == 0);
}

int	spotlight(t_philo *philo)
{
	int flag;

	flag = FALSE;
	pthread_mutex_lock(&philo->spotlight_lock);
	if(philo->spotlight % 2 == 0)
		flag = TRUE;
	pthread_mutex_unlock(&philo->spotlight_lock);
	return (flag);
}

void	*dinning_table(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (all_alive(philo->info) == TRUE)
	{
		if (spotlight(philo) == ON)
		{
			while (forks_available(philo) == FALSE)
			{
				if (precise_usleep(philo, 10) == 0)
					break ;
			}
			mutex_lock(&philo->info->fork_locks[philo->own_fork],
				&philo->info->forks[philo->own_fork], philo->id);
			write_lock(philo->info, philo, "HAS TAKEN A FORK ON SPOTLIGHT:",
				ORANGE);
			mutex_lock(&philo->info->fork_locks[philo->other_fork],
				&philo->info->forks[philo->other_fork], philo->id);
			write_lock(philo->info, philo, "HAS TAKEN A FORK ON SPOTLIGHT:",
				ORANGE);
			eating(philo, philo->id - 1);
			sleeping(philo, philo->id - 1);
		}
		else
			thinking(philo, philo->id - 1);
	}
	return (NULL);
}
