/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:16:55 by maakhan           #+#    #+#             */
/*   Updated: 2024/10/23 16:29:59 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	process_creation(t_philo *philo, t_info *info, pthread_t *chef)
{
	int	i;
	int	pid;

	i = 0;
	while (i < info->philo_count)
	{
		pid = fork();
		if (pid == -1)
			ft_error(FORK_FAIL);
		else if (pid == 0)
		{
			if (i == 0)
				create_thread(chef, &kitchen, info);
			create_thread(&philo->reaper, &graveyard, (void *)philo);
			dinning(&philo[i], info);
			sema_close(info);
			join_thread(&philo->reaper);
			if (i == 0)
				join_thread(chef);
			exit(EXIT_SUCCESS);
		}
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_philo		philo[MAX_PHILOS];
	t_info		info;
	pthread_t	chef;

	sema_unlink(&info);
	if (argc == 5 || argc == 6)
	{
		parsing(argc, argv);
		init_info(argv, &info);
		init_philos(argv, philo, &info);
		process_creation(philo, &info, &chef);
		waiting(&info);
		return (0);
	}
	ft_error(WRONG_FORMAT);
}
