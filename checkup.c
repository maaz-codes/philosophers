/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 10:13:41 by maakhan           #+#    #+#             */
/*   Updated: 2024/10/09 16:15:32 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int check_alive(t_doctor *doctor)
{
	int flag;

	flag = FALSE;
	pthread_mutex_lock(doctor->lock);
	if (doctor->info->all_alive == TRUE)
		flag = TRUE;
	pthread_mutex_unlock(doctor->lock);
	return (flag);
}

static int is_dead(t_doctor *doctor, int i)
{
    long long time;
    int flag;
    
    time = get_exact_time() - doctor->philo[i]->start_time;
    flag = 0;
    if (time > doctor->philo[i]->time_to_die)
    {
        write_lock(doctor->philo[i], "HAS DIED", RED);
        pthread_mutex_lock(doctor->lock);
        doctor->info->all_alive = FALSE;
        flag = 1;
        pthread_mutex_unlock(doctor->lock);
    }
    return (flag);
}

static int all_ate(t_doctor *doctor, int i, int *count)
{
    int flag;

    flag = 0;
    if (doctor->philo[i]->meal_count >= doctor->philo[i]->max_meals)
    {
        (*count) += 1;
        pthread_mutex_lock(doctor->lock);
        if ((*count) == doctor->info->philo_count) // all have eaten
        {
            doctor->info->all_alive = FALSE;
            printf("\033[1;36m %lld DINNER IS OVER \n\033[0m", get_exact_time());	
        }
        pthread_mutex_unlock(doctor->lock);
    }
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
	while (check_alive(doctor) == TRUE)
	{	
		while (i < doctor->info->philo_count)
        {
            if (is_dead(doctor, i) == TRUE || all_ate(doctor, i, &count) == TRUE)
                break ;
            i++;
        }
		precise_usleep(100); // Added to prevent busy waiting
	}
	return (NULL);
}
