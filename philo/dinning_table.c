/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinning_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 14:25:48 by maakhan           #+#    #+#             */
/*   Updated: 2024/11/04 18:31:57 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*one_philo(t_philo *philo)
{
	write_lock(philo->info, philo, "is thinking");
	precise_usleep(philo, philo->time_to_die * 1000);
	return (NULL);
}

int	spotlight(t_philo *philo)
{
	int	flag;

	flag = FALSE;
	if (philo->spotlight % 2 == 0)
		flag = TRUE;
	return (flag);
}

void	*dinning_table(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (all_alive(philo->info) == TRUE)
	{
		if (philo->philo_count == 1)
			return (one_philo(philo));
		if (spotlight(philo) == ON)
		{
			if (!eating(philo, philo->id - 1))
				return (NULL);
			if (!sleeping(philo))
				return (NULL);
		}
		else if (!thinking(philo))
			return (NULL);
	}
	return (NULL);
}
