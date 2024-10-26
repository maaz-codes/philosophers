/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:57:39 by maakhan           #+#    #+#             */
/*   Updated: 2024/10/26 20:38:31 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	write_sema(t_info *info, t_philo *philo, char *str)
{
	sem_wait(info->sema_write);
	if (info->all_alive == TRUE && info->all_full == FALSE)
		printf("%lld %i %s\n", get_exact_time()
			- info->start_program_time, philo->id, str);
	sem_post(info->sema_write);
}

int	all_alive(t_philo *philo)
{
	if (get_exact_time() - philo->start_time > philo->time_to_die)
	{
		philo->info->all_alive = FALSE;
		philo->leader = TRUE;
		return (FALSE);
	}
	return (TRUE);
}

int	all_full(t_philo *philo)
{
	if (philo->statiated == TRUE)
		return (TRUE);
	return (FALSE);
}

int	spotlight(t_philo *philo)
{
	int	flag;

	flag = OFF;
	if (philo->spotlight % 2 == 0)
		flag = ON;
	return (flag);
}

void	rotate_spotlight(t_philo *philo)
{
	if (philo->spotlight == philo->philo_count)
		philo->spotlight = 1;
	else
		philo->spotlight += 1;
}
