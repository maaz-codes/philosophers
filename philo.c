/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:45:32 by maakhan           #+#    #+#             */
/*   Updated: 2024/10/02 19:22:50 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *dinning_table(void *args)
{
	t_philo *philo;

	philo = (t_philo *)args;
	// printf("id = %i | own_fork = %i | other_fork = %i\n", philo->id, philo->own_fork, philo->other_fork);
	pthread_mutex_lock(&philo->info->fork_locks[philo->id - 1]);
	philo->info->forks[philo->own_fork] = philo->id;
	philo->info->forks[philo->other_fork] = philo->id;
	printf("\033[1;34m %i GRABBED FORKS %i & %i \033[0m\n", philo->id, philo->own_fork + 1, philo->other_fork + 1);
	pthread_mutex_unlock(&philo->info->fork_locks[philo->id - 1]);
	return (args);
}

int	main(int argc, char *argv[])
{
	t_philo			philo[MAX_PHILOS];
	t_info  		info;
	pthread_mutex_t fork_locks[MAX_PHILOS];
	pthread_t		t[MAX_PHILOS];
	int i;

	if (argc == 5 || argc == 6)
	{
		parsing(argc, argv);
		init_info(argv, &info, fork_locks);
		i = 0;
		while (i < info.philo_count)
		{
			init_philo(argv, &philo[i], &info, i);
			pthread_create(&t[i], NULL, &dinning_table, (void *)&philo[i]);
			i++;
		}
		i = 0;
		while (i < info.philo_count)
		{
			pthread_join(t[i], NULL);
			i++;
		}
		i = 0;
		while (i < info.philo_count)
		{
			pthread_mutex_destroy(&fork_locks[i]);
			printf("%i, ", info.forks[i]);
			i++;
		}
		return (0);
	}
	ft_error(WRONG_FORMAT);
}
