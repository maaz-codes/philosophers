/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:06:50 by maakhan           #+#    #+#             */
/*   Updated: 2024/10/26 20:31:04 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	grab_forks(t_philo *philo)
{
	mutex_lock(&philo->info->fork_locks[philo->own_fork],
		&philo->info->forks[philo->own_fork], philo->id);
	write_lock(philo->info, philo, " has taken a fork");
	mutex_lock(&philo->info->fork_locks[philo->other_fork],
		&philo->info->forks[philo->other_fork], philo->id);
	write_lock(philo->info, philo, " has taken a fork");
}

void	release_forks(t_philo *philo)
{
	mutex_lock(&philo->info->fork_locks[philo->own_fork],
		&philo->info->forks[philo->own_fork], 0);
	mutex_lock(&philo->info->fork_locks[philo->other_fork],
		&philo->info->forks[philo->other_fork], 0);
}

void	sleeping(t_philo *philo)
{
	if (all_alive(philo->info) == TRUE)
	{
		write_lock(philo->info, philo, " is sleeping");
		precise_usleep(philo, philo->time_to_sleep * 1000);
		rotate_spotlight(philo);
	}
}

void	thinking(t_philo *philo)
{
	if (all_alive(philo->info) == TRUE)
	{
		write_lock(philo->info, philo, "is thinking");
		if (precise_usleep(philo, (philo->time_to_eat / 2) * 1000) == 0)
			return ;
		while (all_eating(philo) == TRUE)
		{
			if (precise_usleep(philo, 100) == 0)
				return ;
		}
		rotate_spotlight(philo);
	}
}

void	eating(t_philo *philo, int i)
{
	if (all_alive(philo->info) == TRUE)
	{
		grab_forks(philo);
		write_lock(philo->info, philo, "is eating");
		precise_usleep(philo, philo->time_to_eat / 2 * 1000);
		mutex_lock(&philo->info->eat_lock, &philo->info->eating, TRUE);
		precise_usleep(philo, philo->time_to_eat / 2 * 1000);
		release_forks(philo);
		pthread_mutex_lock(&philo->meal_lock);
		philo->meal_count += 1;
		if (philo->max_meals == -1)
			philo->statiated = FALSE;
		else if (philo->meal_count >= philo->max_meals)
			philo->statiated = TRUE;
		pthread_mutex_unlock(&philo->meal_lock);
		mutex_lock(&philo->info->eat_lock, &philo->info->eating, FALSE);
		pthread_mutex_lock(&philo->info->reset_lock[i]);
		philo->start_time = get_exact_time();
		pthread_mutex_unlock(&philo->info->reset_lock[i]);
		rotate_spotlight(philo);
	}
}
