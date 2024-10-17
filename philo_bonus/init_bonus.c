/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:45:50 by maakhan           #+#    #+#             */
/*   Updated: 2024/10/17 19:28:51 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void init_info(char *argv[], t_info *info)
{
	int i;

	info->start_program_time = get_exact_time();
	info->philo_count = ft_atoi(argv[1]);
	info->all_alive = TRUE;
	info->eating = FALSE;
	info->meals_done = FALSE;
	info->sema_write = sem_open(SEMA_WRITE, O_CREAT, 0644, 1);
	info->sema_light = sem_open(SEMA_LIGHT, O_CREAT, 0644, 1);
	info->sema_eat = sem_open(SEMA_EAT, O_CREAT, 0644, info->philo_count / 2);
	info->sema_think = sem_open(SEMA_THINK, O_CREAT, 0644, 0);
	info->sema_death = sem_open(SEMA_DEATH, O_CREAT, 0644, 0);
	i = 0;
	while (i < info->philo_count)
	{
		info->forks[i] = 0;
		i++;
	}
}

void init_philos(char **argv, t_philo *philo, t_info *info)
{
	int i;

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		philo[i].info = info;
		philo[i].id = i + 1;
		philo[i].spotlight = i + 1;
		philo[i].philo_count = info->philo_count;
		philo[i].own_fork = i; // philo->id
		philo[i].other_fork = (i + 1) % info->philo_count;
		philo[i].time_to_die = ft_atoi(argv[2]);
		philo[i].time_to_eat = ft_atoi(argv[3]);
		philo[i].time_to_sleep = ft_atoi(argv[4]);
		if (argv[5])
			philo[i].max_meals = ft_atoi(argv[5]);
		else
			philo[i].max_meals = -1;
		philo[i].meal_count = 0;
		philo[i].statiated = FALSE;
		philo[i].start_time = get_exact_time();
		i++;
	}
}
