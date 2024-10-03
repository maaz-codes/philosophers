/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:45:50 by maakhan           #+#    #+#             */
/*   Updated: 2024/10/03 14:08:44 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void print_lock(long long ts, t_philo *philo, char *str)
// {
// 	pthread_mutex_lock(philo->info->print_locks);
// 	printf("%lld %i %s", ts, philo->id, str);
// 	pthread_mutex_unlock(philo->info->print_locks);
// 	// timestamp_in_ms X has taken a fork
// }

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

	info->philo_count = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
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

void init_philo(char **argv, t_philo *philo, t_info *info, int index)
{
	philo->info = info;
	philo->id = index + 1;
	philo->own_fork = index; // philo->id
	if (philo->id % 2 == 0) // even
		philo->other_fork = index - 1;
	else // odd
	{
		if (philo->id == info->philo_count) // last_index
			philo->other_fork = 1; // first_index
		else
			philo->other_fork = index + 1;
	}
	philo->meal_count = 0;
	philo->start_time = get_exact_time();
	philo->starved = FALSE;
}
