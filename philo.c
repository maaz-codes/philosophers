/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:45:32 by maakhan           #+#    #+#             */
/*   Updated: 2024/10/07 20:48:29 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void init_doctor(t_doctor *doctor, t_info *info, t_philo *philo)
{
	doctor->info = info;
	doctor->philo = philo;
}

void *checkup(void *args)
{
	t_doctor *doctor;
	int i;

	doctor = (t_doctor *)args;
	i = 0;
	while (doctor->info->all_alive == TRUE)
	{	
		i = 0;
		while (i < doctor->info->philo_count)
		{
			long long time = get_exact_time() - doctor->philo[i].start_time;
			if (time > doctor->info->time_to_die)
			{
				doctor->info->all_alive = FALSE;
				printf("\033[1;36m %lld %i JUST DIED \n\033[0m", get_exact_time() - doctor->info->start_program_time, doctor->philo[i].id);
				break ;
			}	
			else if (doctor->philo[i].meal_count == doctor->info->max_meals)
			{
				doctor->info->all_alive = FALSE;
				printf("\033[1;36m %lld DINNER IS OVER \n\033[0m", get_exact_time());
				break ;
			}
			i++;
		}
	}
	return (args);
}

int	main(int argc, char *argv[])
{
	t_philo			philo[MAX_PHILOS];
	t_info  		info;
	pthread_t		t[MAX_PHILOS];
	pthread_mutex_t fork_locks[MAX_PHILOS];
	pthread_mutex_t print_locks[MAX_PHILOS];
	pthread_t		td;
	t_doctor		doctor;
	int 			i;

	if (argc == 5 || argc == 6)
	{
		parsing(argc, argv);
		init_info(argv, &info, fork_locks, print_locks);
		i = 0;
		while (i < info.philo_count)
		{
			init_philo(argv, &philo[i], &info, i);
			pthread_create(&t[i], NULL, &dinning_table, (void *)&philo[i]);
			i++;
		}
		init_doctor(&doctor, &info, philo);
		pthread_create(&td, NULL, &checkup, (void *)&doctor);
		join_and_destroy(t, &info, fork_locks, print_locks);
		pthread_join(td, NULL);
		return (0);
	}
	ft_error(WRONG_FORMAT);
}
