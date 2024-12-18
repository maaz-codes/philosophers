/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:45:50 by maakhan           #+#    #+#             */
/*   Updated: 2024/11/04 18:20:13 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_info(char *argv[], t_info *info)
{
	int	i;

	info->start_program_time = get_exact_time();
	info->philo_count = ft_atoi(argv[1]);
	info->all_alive = TRUE;
	info->eating = TRUE;
	info->meals_done = FALSE;
	i = 0;
	while (i < info->philo_count)
	{
		info->forks[i] = -1;
		i++;
	}
}

void	init_philos(char **argv, t_philo *philo, t_info *info)
{
	int	i;

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		philo[i].info = info;
		philo[i].id = i + 1;
		philo[i].spotlight = i + 1;
		philo[i].philo_count = info->philo_count;
		philo[i].own_fork = i;
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
		philo[i].thinked = TRUE;
		philo[i].slept = FALSE;
		philo[i].start_time = get_exact_time();
		i++;
	}
}

void	init_mutexes(t_info *info, t_philo *philo)
{
	int	i;

	if (pthread_mutex_init(&info->print_lock, NULL) != 0)
		ft_error(MUTEX_FAIL);
	if (pthread_mutex_init(&info->eat_lock, NULL) != 0)
		ft_error(MUTEX_FAIL);
	if (pthread_mutex_init(&info->alive_lock, NULL) != 0)
		ft_error(MUTEX_FAIL);
	i = 0;
	while (i < info->philo_count)
	{
		if (pthread_mutex_init(&info->fork_locks[i], NULL) != 0)
			ft_error(MUTEX_FAIL);
		if (pthread_mutex_init(&info->f_register_locks[i], NULL) != 0)
			ft_error(MUTEX_FAIL);
		if (pthread_mutex_init(&info->reset_lock[i], NULL) != 0)
			ft_error(MUTEX_FAIL);
		if (pthread_mutex_init(&philo[i].spotlight_lock, NULL) != 0)
			ft_error(MUTEX_FAIL);
		if (pthread_mutex_init(&philo[i].meal_lock, NULL) != 0)
			ft_error(MUTEX_FAIL);
		i++;
	}
}

void	init_doctor(t_doctor *doctor, t_info *info, t_philo *philo)
{
	doctor->info = info;
	doctor->philo = philo;
	doctor->philo_count = info->philo_count;
	doctor->time_to_die = philo[0].time_to_die;
}
