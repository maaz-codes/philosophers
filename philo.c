/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:45:32 by maakhan           #+#    #+#             */
/*   Updated: 2024/10/03 07:11:47 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_philo			philo[MAX_PHILOS];
	t_info  		info;
	pthread_t		t[MAX_PHILOS];
	pthread_mutex_t fork_locks[MAX_PHILOS];
	pthread_mutex_t print_locks[MAX_PHILOS];
	int i;

	if (argc == 5 || argc == 6)
	{
		parsing(argc, argv);
		init_info(argv, &info, fork_locks, print_locks);
		i = 0;
		while (i < info.philo_count)
		{
			init_philo(argv, &philo[i], &info, i);
			pthread_create(&t[i], NULL, &dinning_table, (void *)&philo[i]);
			i++;
		}
		join_and_destroy(t, &info, fork_locks, print_locks);
		return (0);
	}
	ft_error(WRONG_FORMAT);
}
