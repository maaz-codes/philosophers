/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 10:13:41 by maakhan           #+#    #+#             */
/*   Updated: 2024/10/10 16:27:45 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int is_dead(t_doctor *doctor, int i)
{
    long long time;
    int flag;
    
    // race_condition ?
    pthread_mutex_lock(&doctor->philo[i].reset_lock[i]);
    time = get_exact_time() - doctor->philo->start_time;
    pthread_mutex_unlock(&doctor->philo[i].reset_lock[i]);
    flag = FALSE;
    // race_condition ?
    if (time > doctor->philo[i].time_to_die)
    {
        write_lock(doctor->info, &doctor->philo[i], "HAS DIED", RED);
        pthread_mutex_lock(&doctor->info->alive_lock);
        doctor->info->all_alive = FALSE;
        flag = TRUE;
        pthread_mutex_unlock(&doctor->info->alive_lock);
    }
    return (flag);
}

static int all_ate(t_doctor *doctor, int i, int *count)
{
    int flag;

    flag = 0;
    // race_condition ?
    if (doctor->philo[i].statiated == TRUE)
    {
        (*count) += 1;
        doctor->philo[i].statiated = FALSE;
    }
    pthread_mutex_lock(&doctor->info->alive_lock);
    if ((*count) >= doctor->info->philo_count) // all ate
    {
        flag = 1;
        doctor->info->all_alive = FALSE;
        pthread_mutex_lock(&doctor->info->print_lock);
        printf("\033[1;36m%lld DINNER IS OVER \n\033[0m", get_exact_time() - doctor->info->start_program_time);	
        pthread_mutex_unlock(&doctor->info->print_lock);
    }
    pthread_mutex_unlock(&doctor->info->alive_lock);
    return (flag);
}

void *checkup(void *args)
{
	t_doctor *doctor;
    int count;
    int i;

    i = 0;
    count = 0;
	doctor = (t_doctor *)args;
    while (all_alive(doctor->info) == TRUE)
	{
        i = 0;
		while (i < doctor->philo_count)
        {
            if (is_dead(doctor, i) == TRUE || all_ate(doctor, i, &count) == TRUE)
                break ;
            i++;
        }
		precise_usleep(100); // Added to prevent busy waiting
	}
	return (NULL);
}
