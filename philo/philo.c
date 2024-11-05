/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:45:32 by maakhan           #+#    #+#             */
/*   Updated: 2024/11/04 18:12:47 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	thread_creation(t_philo *philo, t_info *info)
{
	int	i;

	i = 0;
	while (i < info->philo_count)
	{
		create_thread(&philo->t[i], &dinning_table, (void *)&philo[i]);
		i++;
	}
}

static void	join_and_destroy(t_info *info, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->philo_count)
	{
		join_thread(&philo->t[i]);
		i++;
	}
	i = 0;
	pthread_mutex_destroy(&info->print_lock);
	pthread_mutex_destroy(&info->eat_lock);
	pthread_mutex_destroy(&info->alive_lock);
	while (i < info->philo_count)
	{
		pthread_mutex_destroy(&info->fork_locks[i]);
		pthread_mutex_destroy(&info->reset_lock[i]);
		pthread_mutex_destroy(&philo[i].spotlight_lock);
		pthread_mutex_destroy(&philo[i].meal_lock);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_philo		philo[MAX_PHILOS];
	t_info		info;
	t_doctor	doctor;
	pthread_t	td;

	if (argc == 5 || argc == 6)
	{
		parsing(argc, argv);
		init_info(argv, &info);
		init_philos(argv, philo, &info);
		init_mutexes(&info, philo);
		init_doctor(&doctor, &info, philo);
		thread_creation(philo, &info);
		pthread_create(&td, NULL, &checkup, (void *)&doctor);
		pthread_join(td, NULL);
		join_and_destroy(&info, philo);
		return (0);
	}
	ft_error(WRONG_FORMAT);
}
