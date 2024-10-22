/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:16:55 by maakhan           #+#    #+#             */
/*   Updated: 2024/10/22 20:00:21 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void sema_close(t_info *info)
{
	sem_close(info->sema_write);
	sem_close(info->sema_light);
	sem_close(info->sema_think);
	sem_close(info->sema_death);
	sem_close(info->sema_forks);
}

void sema_unlink(t_info *info)
{
	sem_unlink(SEMA_WRITE);
	sem_unlink(SEMA_LIGHT);
	sem_unlink(SEMA_THINK);
	sem_unlink(SEMA_DEATH);
	sem_unlink(SEMA_FORKS);
}

void massacre(t_philo *philo)
{
	int i;

	i = 0;
	sem_wait(philo->info->sema_write);
	if (philo->info->dinner_ended == FALSE)
	{
		if (philo->info->all_alive == FALSE)
			printf("%lld %i is Dead\n", get_exact_time() - philo->info->start_program_time, philo->id);
		else	
			printf("%lld DINNER IS OVER\n", get_exact_time() - philo->info->start_program_time);
		sem_post(philo->info->sema_death);
	}
	usleep(50 * 1000);
	sem_post(philo->info->sema_write);
}

void dinning(t_philo *philo, t_info *info)
{
	while (info->all_alive == TRUE && info->all_full == FALSE)
	{
		if (spotlight(philo) == OFF)
		{
			if (philo->slept == FALSE)
				if (!thinking(info, philo))
					break ;
			sem_wait(info->sema_think); 
			philo->slept = FALSE;
		}
		if (spotlight(philo) == ON)
		{
			if (!eating(info, philo))
				break ;
			if (!sleeping(info, philo))
				break ;
			philo->slept = TRUE;
		}
	}
	if (philo->leader == TRUE)
		massacre(philo);
}

void *graveyard(void *args)
{
	t_philo *philo;
	int i;

	philo = (t_philo *)args;
	sem_wait(philo->info->sema_death);
	i = 0;
	while (i < philo->philo_count)
	{
		sem_post(philo->info->sema_death);
		i++;
	}
	exit(EXIT_SUCCESS);
	return (NULL);
}

void process_creation(t_philo *philo, t_info *info)
{
	int i;
	int pid;

	i = 0;
	info->start_program_time = get_exact_time();
	while (i < info->philo_count)
	{
		pid = fork();
		if (pid == -1)
			ft_error(FORK_FAIL); // change it to process fail
		else if (pid == 0)
		{
			pthread_create(&philo->reaper, NULL, &graveyard, (void *)philo);
			dinning(&philo[i], info);
			sema_close(info);
			pthread_join(philo->reaper, NULL);
			exit(EXIT_SUCCESS);
		}
		i++;
	}
	printf("TIME after all forks: %lld.................................\n", get_exact_time() - info->start_program_time);
}

void waiting(t_info *info)
{
	int i;

	i = 0;
	while(i < info->philo_count)
	{
		wait(NULL);
		i++;
	}	 
	sema_close(info);
	sema_unlink(info);
}

int	main(int argc, char *argv[])
{
	t_philo			philo[MAX_PHILOS];
	t_info  		info;

	sema_unlink(&info);
	if (argc == 5 || argc == 6)
	{
		parsing(argc, argv);
		init_info(argv, &info);
		init_philos(argv, philo, &info);   
		process_creation(philo, &info);
		waiting(&info);
		return (0);
	}
	ft_error(WRONG_FORMAT);
}
