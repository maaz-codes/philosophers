/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinning_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 14:25:48 by maakhan           #+#    #+#             */
/*   Updated: 2024/10/26 20:20:25 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		if (spotlight(philo) == ON)
		{
			eating(philo, philo->id - 1);
			sleeping(philo);
		}
		else
			thinking(philo);
	}
	return (NULL);
}
