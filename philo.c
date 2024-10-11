/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:45:32 by maakhan           #+#    #+#             */
/*   Updated: 2024/10/11 12:12:39 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void thread_creation(t_philo *philo, t_info *info)
{
	int i;

	i = 0;
	while (i < info->philo_count)
	{
		pthread_create(&philo->t[i] , NULL, &dinning_table, (void *)&philo[i]);
		i++;
	}
}

void join_and_destroy(t_info *info, t_philo *philo)
{
	int i;
	
	i = 0;
	while (i < philo->philo_count)
	{
		pthread_join(philo->t[i], NULL);
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
		printf("%i, ", info->forks[i]);
		i++;
	}
}

void print_info(t_philo *philo)
{
	int i = 0;
	while (i < philo[i].philo_count)
	{
		printf("%i, ", philo[i].own_fork);
		i++;
	}
}


int	main(int argc, char *argv[])
{
	t_philo			philo[MAX_PHILOS];
	t_info  		info;
	t_doctor		doctor;
	pthread_t		td;
	
	if (argc == 5 || argc == 6)
	{
		parsing(argc, argv);
		init_info(argv, &info);
		init_philos(argv, philo, &info);
		init_doctor(&doctor, &info, philo);
		thread_creation(philo, &info);
		pthread_create(&td, NULL, &checkup, (void *)&doctor);
		pthread_join(td, NULL);
		join_and_destroy(&info, philo);
		return (0);
	}
	ft_error(WRONG_FORMAT);
}
