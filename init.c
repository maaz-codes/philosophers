/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:45:50 by maakhan           #+#    #+#             */
/*   Updated: 2024/10/09 09:43:15 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int *init_chairs(int chair_count)
{
	int i;
	int *chairs;
	
	chairs = malloc(sizeof(int) * chair_count);
	if (!chairs)
		(printf("Chair-malloc failed!\n"), exit(EXIT_FAILURE));
	i = 0;
	while (i < chair_count)
	{
		chairs[i] = i + 1;
		i++;
	}
	return (chairs);
}

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
		forks[i] = 0;
		i++;
	}
	return (forks);
}

void init_info(char *argv[], t_info *info, pthread_mutex_t *fork_locks, pthread_mutex_t *print_locks)
{
	int i;

	info->start_program_time = get_exact_time();
	info->philo_count = ft_atoi(argv[1]);
	if (argv[5])
		info->max_meals = ft_atoi(argv[5]);
	else
		info->max_meals = -1;
	info->meals_done = FALSE;
	info->all_alive = TRUE;
	info->forks = init_forks(info->philo_count);
	info->fork_locks = fork_locks;
	info->print_locks = print_locks;
	i = 0;
	while (i < info->philo_count)
	{
		if (pthread_mutex_init(&info->fork_locks[i], NULL) != 0)
            (free(info->forks), ft_error(MUTEX_F));
		i++;
	}
	i = 0;
	while (i < info->philo_count)
	{
		if (pthread_mutex_init(&info->print_locks[i], NULL) != 0)
            (free(info->forks), ft_error(MUTEX_P));
		i++;
	}
}

void init_philos(char **argv, t_philo **philo, t_info *info)
{
	int i;

	i = 0;
	while (i < info->philo_count)
	{
		philo[i]->info = info;
		philo[i]->id = i + 1;
		philo[i]->spotlight = i + 1;
		philo[i]->own_fork = i; // philo->id
		philo[i]->other_fork = (i + 1) % info->philo_count;
		philo[i]->time_to_die = ft_atoi(argv[2]);
		philo[i]->time_to_eat = ft_atoi(argv[3]);
		philo[i]->time_to_sleep = ft_atoi(argv[4]);
		philo[i]->meal_count = 0;
		philo[i]->start_time = get_exact_time();
		i++;
	}
}
