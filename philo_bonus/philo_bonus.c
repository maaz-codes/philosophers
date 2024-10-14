/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:16:55 by maakhan           #+#    #+#             */
/*   Updated: 2024/10/14 22:07:10 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// static void thread_creation(t_philo *philo, t_info *info)
// {
// 	int i;

// 	i = 0;
// 	while (i < info->philo_count)
// 	{
// 		pthread_create(&philo->t[i] , NULL, &dinning_table, (void *)&philo[i]);
// 		i++;
// 	}
// }

// static void join_and_destroy(t_info *info, t_philo *philo)
// {
// 	int i;
	
// 	i = 0;
// 	while (i < philo->philo_count)
// 	{
// 		pthread_join(philo->t[i], NULL);
// 		i++;
// 	}
// 	i = 0;
// 	pthread_mutex_destroy(&info->print_lock);
// 	pthread_mutex_destroy(&info->eat_lock);
// 	pthread_mutex_destroy(&info->alive_lock);
// 	while (i < info->philo_count)
// 	{
// 		pthread_mutex_destroy(&info->fork_locks[i]);
// 		pthread_mutex_destroy(&info->reset_lock[i]);
// 		pthread_mutex_destroy(&philo[i].spotlight_lock);
// 		pthread_mutex_destroy(&philo[i].meal_lock);
// 		i++;
// 	}
// }

void dinning(t_philo *philo, t_info *info, t_sema *sema)
{
	// sem_wait(sema);
	// printf("%lld PHILO %i ARRIVED\n", get_exact_time() - info->start_program_time, philo->id);
	while (1)
	{
		if (spotlight(philo, sema) == OFF)
		{
			precise_usleep(info, 100);	
			write_sema(info , philo, "HAS STARTED THINKING\n", sema);
			rotate_spotlight(philo);
		}
		sem_wait(sema->sema_philo);
		if (spotlight(philo, sema) == ON)
		{
			// sem_wait(sema->sema_write);
			write_sema(info , philo, "HAS STARTED EATING", sema);
			// printf("%lld %i HAS STARTED EATING\n", get_exact_time() - info->start_program_time, philo->id);
			// sem_post(sema->sema_write);
			// precise_usleep(info, philo->time_to_eat);
			precise_usleep(info, 1000 * 1000); // eating
			rotate_spotlight(philo);
			
			// sem_wait(sema->sema_write);
			write_sema(info , philo, "HAS STARTED EATING", sema);
			// printf("%lld %i HAS STARTED SLEEPING\n", get_exact_time() - info->start_program_time, philo->id);
			// sem_post(sema->sema_write);
			precise_usleep(info, 1000 * 1000); // sleeping
			rotate_spotlight(philo);
		}
		else
		{
			write_sema(info , philo, "HAS STARTED THINKING", sema);
			// printf("%lld %i HAS STARTED THINKING\n", get_exact_time() - info->start_program_time, philo->id);
			precise_usleep(info, 1000 * 1000);
			rotate_spotlight(philo);
		}
		sem_post(sema->sema_philo);
	}
	// sleep(1);
	// sem_post(sema);
}

void process_creation(t_philo *philo, t_info *info, t_sema *sema)
{
	int i;
	int pid;

	i = 0;
	while (i < info->philo_count)
	{
		pid = fork();
		if (pid == -1)
			ft_error(MUTEX_FAIL); // change it to process fail
		if (pid == 0)
		{
			dinning(&philo[i], info, sema);
			sem_close(sema->sema_light);
			sem_close(sema->sema_write);
			exit(EXIT_SUCCESS);
		}
		i++;
	}
}

void waiting(t_info *info, t_sema *sema)
{
	int i;

	i = 0;
	while(i < info->philo_count)
	{
		wait(NULL);
		i++;
	}	
	sem_close(sema->sema_philo);
	sem_close(sema->sema_light);
	sem_close(sema->sema_write);
	sem_unlink(SEMA_PHILO);
	sem_unlink(SEMA_LIGHT);
	sem_unlink(SEMA_WRITE);
}

int	main(int argc, char *argv[])
{
	t_philo			philo[MAX_PHILOS];
	t_info  		info;
	t_doctor		doctor;
	pthread_t		td;
	// sem_t 			*sem;
	t_sema			*sema;
	
	sema = (t_sema *)malloc(sizeof(t_sema));
	if (argc == 5 || argc == 6)
	{
		parsing(argc, argv);
		init_info(argv, &info);
		init_philos(argv, philo, &info);
		// sem = sem_open(SEMA_NAME, O_CREAT, 0664, info.philo_count);
		printf("running\n");
		sema->sema_light = sem_open(SEMA_LIGHT, O_CREAT, 0664, 1);
		sema->sema_write = sem_open(SEMA_WRITE, O_CREAT, 0664, 1);
		sema->sema_philo = sem_open(SEMA_WRITE, O_CREAT, 0664, info.philo_count / 2);
		// init_mutexes(&info, philo);
		// init_doctor(&doctor, &info, philo);
		// thread_creation(philo, &info);
		process_creation(philo, &info, sema);
		waiting(&info, sema);
		// pthread_create(&td, NULL, &checkup, (void *)&doctor);
		// pthread_join(td, NULL);
		// join_and_destroy(&info, philo);
		return (0);
	}
	ft_error(WRONG_FORMAT);
}
