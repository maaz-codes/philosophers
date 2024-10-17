/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:06:50 by maakhan           #+#    #+#             */
/*   Updated: 2024/10/16 13:32:05 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// void eating(t_info *info, t_philo *philo, t_sema *sema)
// {
//     // sem_wait(sema->sema_write);
//     write_sema(info , philo, "HAS STARTED EATING", sema);
//     // printf("%lld %i HAS STARTED EATING\n", get_exact_time() - info->start_program_time, philo->id);
//     // sem_post(sema->sema_write);
//     // precise_usleep(info, philo->time_to_eat);
//     precise_usleep(info, 1000 * 1000); // eating
//     rotate_spotlight(philo);
// }

// void sleeping(t_info *info, t_philo *philo, t_sema *sema)
// {
//     // sem_wait(sema->sema_write);
//     write_sema(info , philo, "HAS STARTED SLEEPING", sema);
//     // printf("%lld %i HAS STARTED SLEEPING\n", get_exact_time() - info->start_program_time, philo->id);
//     // sem_post(sema->sema_write);
//     precise_usleep(info, 1000 * 1000); // sleeping
//     rotate_spotlight(philo);
// }

// void thinking(t_info *info, t_philo *philo, t_sema *sema)
// {
//     precise_usleep(info, 1000 * 1000);	
//     printf("enter\n");
//     // sem_wait(sema->sema_write);
//     // printf("THINKING\n");
//     // sem_post(sema->sema_write);
//     write_sema(info , philo, "HAS STARTED THINKING\n", sema);
//     // printf("running\n");
//     rotate_spotlight(philo);
// }
