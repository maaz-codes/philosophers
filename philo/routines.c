/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:06:50 by maakhan           #+#    #+#             */
/*   Updated: 2024/11/04 18:22:41 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sleeping(t_philo *philo)
{
	if (all_alive(philo->info) == TRUE)
	{
		write_lock(philo->info, philo, " is sleeping");
		if (!precise_usleep(philo, philo->time_to_sleep * 1000))
			return (0);
		rotate_spotlight(philo);
		return (1);
	}
	return (0);
}

int	thinking(t_philo *philo)
{
	if (all_alive(philo->info) == TRUE)
	{
		write_lock(philo->info, philo, "is thinking");
		if (!precise_usleep(philo, (philo->time_to_eat * 0.5) * 1000))
			return (0);
		while (!forks_available(philo))
			usleep(100);
		rotate_spotlight(philo);
		return (1);
	}
	return (0);
}

int	eating(t_philo *philo, int i)
{
	if (all_alive(philo->info) == TRUE)
	{
		grab_forks(philo);
		write_lock(philo->info, philo, "is eating");
		if (!precise_usleep(philo, (philo->time_to_eat * 0.25) * 1000))
			return (0);
		register_forks(philo);
		precise_usleep(philo, (philo->time_to_eat * 0.75) * 1000);
		release_forks(philo);
		deregister_forks(philo);
		pthread_mutex_lock(&philo->info->reset_lock[i]);
		philo->start_time = get_exact_time();
		pthread_mutex_unlock(&philo->info->reset_lock[i]);
		pthread_mutex_lock(&philo->meal_lock);
		philo->meal_count += 1;
		if (philo->max_meals == -1)
			philo->statiated = FALSE;
		else if (philo->meal_count >= philo->max_meals)
			philo->statiated = TRUE;
		pthread_mutex_unlock(&philo->meal_lock);
		rotate_spotlight(philo);
		return (1);
	}
	return (0);
}
