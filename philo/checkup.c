/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 10:13:41 by maakhan           #+#    #+#             */
/*   Updated: 2024/10/26 20:32:54 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_doctor *doctor, int i)
{
	long long	time;
	int			flag;

	pthread_mutex_lock(&doctor->info->reset_lock[i]);
	time = get_exact_time() - doctor->philo[i].start_time;
	pthread_mutex_unlock(&doctor->info->reset_lock[i]);
	flag = FALSE;
	if (time > doctor->time_to_die)
	{
		mutex_lock(&doctor->info->alive_lock, &doctor->info->all_alive, FALSE);
		pthread_mutex_lock(&doctor->info->print_lock);
		printf("%lld %i died\n", get_exact_time()
			- doctor->info->start_program_time, doctor->philo[i].id);
		pthread_mutex_unlock(&doctor->info->print_lock);
		flag = TRUE;
	}
	return (flag);
}

int	all_ate(t_doctor *doctor, int i, int *count)
{
	int	flag;

	flag = 0;
	pthread_mutex_lock(&doctor->philo[i].meal_lock);
	if (doctor->philo[i].statiated == TRUE)
	{
		(*count) += 1;
		doctor->philo[i].statiated = FALSE;
	}
	pthread_mutex_unlock(&doctor->philo[i].meal_lock);
	if (all_alive(doctor->info))
	{
		if ((*count) >= doctor->info->philo_count)
		{
			flag = 1;
			mutex_lock(&doctor->info->alive_lock, &doctor->info->all_alive,
				FALSE);
		}
	}
	return (flag);
}

void	*checkup(void *args)
{
	t_doctor	*doctor;
	int			count;
	int			i;

	i = 0;
	count = 0;
	doctor = (t_doctor *)args;
	while (all_alive(doctor->info) == TRUE)
	{
		i = 0;
		while (i < doctor->philo_count)
		{
			if (is_dead(doctor, i) == TRUE || all_ate(doctor, i,
					&count) == TRUE)
				break ;
			i++;
		}
		usleep(250);
	}
	return (NULL);
}
