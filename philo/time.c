/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:06:45 by maakhan           #+#    #+#             */
/*   Updated: 2024/11/04 00:30:38 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	return ((end.tv_sec - start.tv_sec) * 1000000L + (end.tv_usec
			- start.tv_usec));
}

int	precise_usleep(t_philo *philo, long long usec)
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
		if (all_alive(philo->info) == FALSE)
			return (0);
	}
	return (1);
}

void	write_lock(t_info *info, t_philo *philo, char *str)
{
	pthread_mutex_lock(&info->print_lock);
	if (all_alive(info) == FALSE)
	{
		pthread_mutex_unlock(&info->print_lock);
		return ;
	}
	printf("%lld %i %s\n", get_exact_time()
		- philo->info->start_program_time, philo->id, str);
	pthread_mutex_unlock(&info->print_lock);
}
