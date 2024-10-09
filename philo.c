/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:45:32 by maakhan           #+#    #+#             */
/*   Updated: 2024/10/09 16:21:11 by maakhan          ###   ########.fr       */
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
	while (i < info->philo_count)
	{
		pthread_mutex_destroy(&info->fork_locks[i]);
		pthread_mutex_destroy(&info->print_locks[i]);
		printf("%i, ", info->forks[i]);
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

		thread_creation(philo, &info);
		
		init_doctor(&doctor, &info, philo);
		pthread_create(&td, NULL, &checkup, (void *)&doctor);
		join_and_destroy(&info, philo);
		pthread_join(td, NULL);
		return (0);
	}
	ft_error(WRONG_FORMAT);
}
