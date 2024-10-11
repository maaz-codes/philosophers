/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinning_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 14:25:48 by maakhan           #+#    #+#             */
/*   Updated: 2024/10/11 17:24:20 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	print_forks(t_philo *philo)
// {
// 	int	i;

// 	i = 0;
// 	while (i < philo->info->philo_count)
// 	{
// 		printf("%i, ", philo->info->forks[i]);
// 		i++;
// 	}
// }

int	forks_available(t_philo *philo)
{
	int	own_fork;
	int	other_fork;

	own_fork = 0;
	other_fork = 0;
	mutex_lock(&philo->info->fork_locks[philo->own_fork], &own_fork,
		&philo->info->forks[philo->own_fork]);
	mutex_lock(&philo->info->fork_locks[philo->other_fork], &other_fork,
		&philo->info->forks[philo->other_fork]);
	return (own_fork == 0 && other_fork == 0);
}

int	spotlight(t_philo *philo)
{
	return (philo->spotlight % 2 == 0);
}

int	all_alive(t_info *info)
{
	int	flag;

	flag = FALSE;
	pthread_mutex_lock(&info->alive_lock);
	if (info->all_alive == TRUE)
		flag = TRUE;
	pthread_mutex_unlock(&info->alive_lock);
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
				precise_usleep(1);
			write_lock(philo->info, philo, "HAS TAKEN A FORK ON SPOTLIGHT:",
				ORANGE);
			write_lock(philo->info, philo, "HAS TAKEN A FORK ON SPOTLIGHT:",
				ORANGE);
			mutex_lock(&philo->info->fork_locks[philo->own_fork],
				&philo->info->forks[philo->own_fork], &philo->id);
			mutex_lock(&philo->info->fork_locks[philo->other_fork],
				&philo->info->forks[philo->other_fork], &philo->id);
			eating(philo, philo->id - 1);
			sleeping(philo, philo->id - 1);
		}
		else
			thinking(philo, philo->id - 1);
	}
	return (NULL);
}
