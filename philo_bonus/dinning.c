/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinning.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:53:31 by maakhan           #+#    #+#             */
/*   Updated: 2024/10/26 20:42:13 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	massacre(t_philo *philo)
{
	int	i;

	i = 0;
	sem_wait(philo->info->sema_write);
	if (philo->info->dinner_ended == FALSE)
	{
		if (philo->info->all_alive == FALSE)
			printf("%lld %i is Dead\n", get_exact_time()
				- philo->info->start_program_time, philo->id);
		sem_post(philo->info->sema_death);
	}
	usleep(50 * 10000);
	sem_post(philo->info->sema_write);
}

void	dinning(t_philo *philo, t_info *info)
{
	while (info->all_alive == TRUE && info->all_full == FALSE)
	{
		if (spotlight(philo) == OFF)
		{
			if (philo->slept == FALSE)
				if (!thinking(info, philo))
					break ;
			sem_wait(info->sema_think);
			philo->slept = FALSE;
		}
		if (spotlight(philo) == ON)
		{
			if (!eating(info, philo))
				break ;
			if (!sleeping(info, philo))
				break ;
			philo->slept = TRUE;
		}
	}
	if (philo->leader == TRUE)
		massacre(philo);
}

void	*graveyard(void *args)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)args;
	sem_wait(philo->info->sema_death);
	i = 0;
	while (i < philo->philo_count)
	{
		sem_post(philo->info->sema_death);
		i++;
	}
	exit(EXIT_SUCCESS);
	return (NULL);
}

void	*kitchen(void *args)
{
	t_info	*info;
	int		i;

	info = (t_info *)args;
	i = 0;
	while (i < info->philo_count)
	{
		sem_wait(info->sema_meals);
		i++;
	}
	sem_wait(info->sema_write);
	sem_post(info->sema_death);
	usleep(500);
	sem_post(info->sema_write);
	return (NULL);
}
