/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:16:55 by maakhan           #+#    #+#             */
/*   Updated: 2024/10/17 20:04:27 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	spotlight(t_philo *philo)
{
	int flag;

	flag = OFF;
	if(philo->spotlight % 2 == 0)
		flag = ON;
	return (flag);
}

void rotate_spotlight(t_philo *philo)
{
	if (philo->spotlight == philo->philo_count)
		philo->spotlight = 1;
	else
		philo->spotlight += 1;
}

void release_thinkers(t_info *info, t_philo *philo)
{
	if (philo->spotlight == 2 && philo->philo_count % 2 != 0) 
		sem_post(info->sema_think);
	sem_post(info->sema_think);
}

void eating(t_info *info, t_philo *philo)
{
	write_sema(info, philo, "is eating");
	precise_usleep(info, philo->time_to_eat * 1000);
	philo->start_time = get_exact_time(); // reset_time
	release_thinkers(info, philo);
	rotate_spotlight(philo);
}

void sleeping(t_info *info, t_philo *philo)
{
	write_sema(info, philo, "is sleeping");
	precise_usleep(info, philo->time_to_sleep * 1000);
	rotate_spotlight(philo);
}

void thinking(t_info *info, t_philo *philo)
{
	write_sema(info, philo, "is thinking");
	rotate_spotlight(philo);
	// precise_usleep(info, 100);
}

void sema_unlink(t_info *info)
{
	sem_close(info->sema_write);
	sem_close(info->sema_light);
	sem_close(info->sema_eat);
	sem_close(info->sema_think);
	sem_close(info->sema_death);
	sem_unlink(SEMA_WRITE);
	sem_unlink(SEMA_LIGHT);
	sem_unlink(SEMA_EAT);
	sem_unlink(SEMA_THINK);
	sem_unlink(SEMA_DEATH);
}

void dinning(t_philo *philo, t_info *info)
{
	while (info->all_alive == TRUE)
	{
		if (spotlight(philo) == OFF)
		{
			thinking(info, philo);
			sem_wait(info->sema_think);
		}
		if (spotlight(philo) == ON)
		{
			eating(info, philo);
			sleeping(info, philo);
		}
	}
}

int is_dead(t_philo *philo)
{
	if (get_exact_time() - philo->start_time > philo->time_to_die)
		return (TRUE);
	else
		return (FALSE);
}
int is_full(t_philo *philo)
{
	return (FALSE);
}

void massacre(t_philo *philo)
{
	int i;

	i = 0;
 	while (i < philo->info->philo_count)
	{
		sem_post(philo->info->sema_death);
		i++;
	}
}

void *clinic(void *args)
{
	t_philo *philo;

	philo = (t_philo *)args;
	// race_condition ?
	while (philo->info->all_alive == TRUE)
	{
        if (is_dead(philo) == TRUE || is_full(philo) == TRUE)
            break ;
		precise_usleep(philo->info, 100); // Added to prevent busy waiting
	}
	// race_condition ? 
	philo->info->all_alive = FALSE;
	massacre(philo);
	return (NULL);
}

void *graveyard(void *args)
{
	t_philo *philo;

	philo = (t_philo *)args;
	sem_wait(philo->info->sema_death);
	
	{
		// dinner is over.
		// ending printing...
	}
	return (NULL);
}

void process_creation(t_philo *philo, t_info *info)
{
	int i;
	int pid;

	i = 0;
	while (i < info->philo_count)
	{
		pid = fork();
		if (pid == -1)
			ft_error(MUTEX_FAIL); // change it to process fail
		else if (pid == 0)
		{
			pthread_create(&philo->doc, NULL, &clinic, (void *)philo);
			pthread_create(&philo->reaper, NULL, &graveyard, (void *)philo);
			dinning(&philo[i], info);
			sem_close(info->sema_write);
			exit(EXIT_SUCCESS);
		}
		i++;
	}
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
