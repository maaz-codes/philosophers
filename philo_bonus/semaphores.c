/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:49:20 by maakhan           #+#    #+#             */
/*   Updated: 2024/10/23 14:52:10 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	release_thinkers(t_info *info, t_philo *philo)
{
	int	i;

	if (philo->leader == TRUE)
	{
		i = 0;
		while (i < philo->philo_count)
		{
			sem_post(info->sema_think);
			i++;
		}
		return ;
	}
	if (philo->spotlight == 2 && philo->philo_count % 2 != 0)
		sem_post(info->sema_think);
	sem_post(info->sema_think);
}

void	sema_close(t_info *info)
{
	sem_close(info->sema_write);
	sem_close(info->sema_light);
	sem_close(info->sema_think);
	sem_close(info->sema_death);
	sem_close(info->sema_forks);
	sem_close(info->sema_meals);
}

void	sema_unlink(t_info *info)
{
	sem_unlink(SEMA_WRITE);
	sem_unlink(SEMA_LIGHT);
	sem_unlink(SEMA_THINK);
	sem_unlink(SEMA_DEATH);
	sem_unlink(SEMA_FORKS);
	sem_unlink(SEMA_MEALS);
}

void	waiting(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->philo_count)
	{
		wait(NULL);
		i++;
	}
	sema_close(info);
	sema_unlink(info);
}
