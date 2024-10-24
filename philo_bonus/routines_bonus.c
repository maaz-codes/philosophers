/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:06:50 by maakhan           #+#    #+#             */
/*   Updated: 2024/10/23 14:56:21 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	meal_incrementor(t_philo *philo)
{
	philo->meal_count += 1;
	if (philo->max_meals == philo->meal_count)
		sem_post(philo->info->sema_meals);
	return (1);
}

int	eating(t_info *info, t_philo *philo)
{
	int	flag;

	flag = 0;
	if (info->all_alive == FALSE || info->all_full == TRUE)
	{
		release_thinkers(info, philo);
		return (flag);
	}
	sem_wait(info->sema_forks);
	sem_wait(info->sema_forks);
	write_sema(info, philo, "has taken a fork");
	write_sema(info, philo, "has taken a fork");
	write_sema(info, philo, "is eating");
	if (precise_usleep(philo->time_to_eat * 1000, philo))
	{
		philo->start_time = get_exact_time();
		meal_incrementor(philo);
		flag = 1;
	}
	sem_post(info->sema_forks);
	sem_post(info->sema_forks);
	release_thinkers(info, philo);
	rotate_spotlight(philo);
	return (flag);
}

int	sleeping(t_info *info, t_philo *philo)
{
	if (info->all_alive == FALSE && info->all_full == TRUE)
		return (0);
	write_sema(info, philo, "is sleeping");
	if (!precise_usleep(philo->time_to_sleep * 1000, philo))
		return (0);
	rotate_spotlight(philo);
	return (1);
}

int	thinking(t_info *info, t_philo *philo)
{
	if (info->all_alive == FALSE || info->all_full == TRUE)
		return (0);
	write_sema(info, philo, "is thinking");
	if (philo->philo_count == 1)
		return (precise_usleep(1000 + philo->time_to_die * 1000, philo));
	rotate_spotlight(philo);
	return (1);
}
