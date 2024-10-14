/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:06:50 by maakhan           #+#    #+#             */
/*   Updated: 2024/10/14 22:08:35 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// void eating(t_philo *philo, int i)
// {	
// 	if (all_alive(philo->info) == TRUE)
// 	{
// 		write_lock(philo->info, philo, "IS EATING... ON SPOTLIGHT:", YELLOW);
// 		mutex_lock(&philo->info->eat_lock, &philo->info->eating, TRUE);
// 		// pthread_mutex_lock(&philo->info->eat_lock);
// 		// philo->info->eating = TRUE;
// 		// pthread_mutex_unlock(&philo->info->eat_lock);
// 		precise_usleep(philo->info, philo->time_to_eat * 1000);
// 		mutex_lock(&philo->info->fork_locks[philo->own_fork], &philo->info->forks[philo->own_fork], 0);
// 		// pthread_mutex_lock(&philo->info->fork_locks[philo->own_fork]);
// 		// philo->info->forks[philo->own_fork] = 0;
// 		// pthread_mutex_unlock(&philo->info->fork_locks[philo->own_fork]);
// 		mutex_lock(&philo->info->fork_locks[philo->other_fork], &philo->info->forks[philo->other_fork], 0);
// 		// pthread_mutex_lock(&philo->info->fork_locks[philo->other_fork]);
// 		// philo->info->forks[philo->other_fork] = 0;
// 		// pthread_mutex_unlock(&philo->info->fork_locks[philo->other_fork]);
// 		mutex_lock(&philo->info->eat_lock, &philo->info->eating, FALSE);
// 		// pthread_mutex_lock(&philo->info->eat_lock);
// 		// philo->info->eating = FALSE;
// 		// pthread_mutex_unlock(&philo->info->eat_lock);
// 		pthread_mutex_lock(&philo->meal_lock);
// 		philo->meal_count += 1;
// 		if (philo->max_meals == -1)
// 			philo->statiated = FALSE;
// 		else if (philo->meal_count >= philo->max_meals)
// 			philo->statiated = TRUE;
// 		pthread_mutex_unlock(&philo->meal_lock);
// 		// mutex_lock(&philo->info->reset_lock[i], &philo->start_time, get_exact_time());
// 		pthread_mutex_lock(&philo->info->reset_lock[i]);
// 		philo->start_time = get_exact_time(); // reset_time
// 		pthread_mutex_unlock(&philo->info->reset_lock[i]);
// 		rotate_spotlight(philo);
// 	}
// }

// void sleeping(t_philo *philo, int index)
// {	
// 	if (all_alive(philo->info) == TRUE)
// 	{
// 		write_lock(philo->info, philo, "IS SLEEPING... ON SPOTLIGHT:", PURPLE);
// 		precise_usleep(philo->info, philo->time_to_sleep * 1000);
// 		rotate_spotlight(philo);
// 	}
// }


// void thinking(t_philo *philo, int index)
// {	
// 	write_lock(philo->info, philo, "IS THINKING... ON SPOTLIGHT:", GREEN);
// 	precise_usleep(philo->info, 100);
// 	if (philo->philo_count == 1)
// 		precise_usleep(philo->info, (philo->time_to_die + 1) * 1000);
// 	while (all_eating(philo) == TRUE)
// 	{
// 		precise_usleep(philo->info, 100);
// 	}
// 	rotate_spotlight(philo);
// }
