/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:06:04 by maakhan           #+#    #+#             */
/*   Updated: 2024/10/23 17:09:46 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_error(int flag)
{
	if (flag == WRONG_FORMAT)
	{
		printf("\033[1;31m Enter 4 or 5 args \033[0m\n");
		printf("\033[1;35m [number_of_philosophers] [time_to_die] \033[0m");
		printf("\033[1;35m [time_to_eat] [time_to_sleep] \033[0m");
		printf("\033[1;35m [number_of_meals](optional)\n\033[0m");
		printf("*note : empty string will be considered as 0\n");
	}
	else if (flag == WRONG_CHARS)
		printf("\033[1;31m Enter only numbers \033[0m");
	else if (flag == WRONG_ARGS)
		printf("\033[1;31m READ THE EVALUATION SHEET CORRECTLY :) \033[0m");
	else if (flag == FORK_FAIL)
		printf("\033[1;31m FORK FAILED!\033[0m");
	else if (flag == THREAD_FAIL)
		printf("\033[1;31m THREAD FAILED!\033[0m");
	exit(EXIT_FAILURE);
}

void	create_thread(pthread_t *t, void *(*routine)(void *), void *args)
{
	if (pthread_create(t, NULL, routine, (void *)args) != 0)
		ft_error(THREAD_FAIL);
}

void	join_thread(pthread_t *t)
{
	if (pthread_join(*t, NULL) != 0)
		ft_error(THREAD_FAIL);
}

sem_t	*open_sem(char *name, int value)
{
	sem_t	*sema;

	sema = sem_open(name, O_CREAT, 0644, value);
	if (sema == SEM_FAILED)
		ft_error(SEMA_FAIL);
	return (sema);
}
