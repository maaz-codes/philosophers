/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:06:45 by maakhan           #+#    #+#             */
/*   Updated: 2024/10/21 22:00:10 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long long	get_exact_time(void)
{
	struct timeval	tv;
	long long		ts;

	gettimeofday(&tv, NULL);
	ts = (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000);
	return (ts);
}

static long	get_elapsed_time_microseconds(struct timeval start,
		struct timeval end)
{
	return (end.tv_sec - start.tv_sec) * 1000000L + (end.tv_usec
		- start.tv_usec);
}
int precise_usleep(long usec, t_philo *philo)
{
	struct timeval	start;
	struct timeval	current;
	long			elapsed;
	long			rem;

	elapsed = 0;
	gettimeofday(&start, NULL);
	while (elapsed < usec)
	{
		gettimeofday(&current, NULL);
		elapsed = get_elapsed_time_microseconds(start, current);
		rem = usec - elapsed;
		if (rem > 1000)
			usleep(250);
		if (all_alive(philo) == FALSE || all_full(philo) == TRUE)
			return (0);
			// usleep(rem / 2);
	}
	return (1);
}
