/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:45:50 by maakhan           #+#    #+#             */
/*   Updated: 2024/10/02 18:53:18 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int *init_forks(int fork_count)
{
	int i;
	int *forks;

	forks = malloc(sizeof(int) * fork_count);
	if (!forks)
		(printf("Fork-malloc failed!\n"), exit(EXIT_FAILURE));
	i = 0;
	while (i < fork_count)
	{
		forks[i] = -1;
		i++;
	}
	return (forks);
}

void init_philo_info(char *argv[], t_info *info, pthread_mutex_t *fork_locks)
{
	int i;

	info->philo_count = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	info->meal_count = 4;
	info->all_alive = TRUE;
	info->forks = init_forks(info->philo_count);
	info->fork_locks = fork_locks;
	i = 0;
	while (i < info->philo_count)
	{
		if (pthread_mutex_init(&info->fork_locks[i], NULL) != 0)
            (free(info->forks), ft_error(MUTEX_F));
		i++;
	}
}

void init_philo(char **argv, t_philo *philo, t_info *info, int i)
{
	philo->info = info;
	philo->id = i + 1;
	philo->own_fork = i; // philo->id
	if (philo->id == info->philo_count)
		philo->other_fork = 0; 
	else
		philo->other_fork = i + 1; //(philo->id + 1)
	philo->meal_count = info->meal_count;
}
