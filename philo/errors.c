/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:06:04 by maakhan           #+#    #+#             */
/*   Updated: 2024/10/11 18:03:06 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error(int flag)
{
	if (flag == WRONG_FORMAT)
	{
		printf("\033[1;31m Enter 4 or 5 args \033[0m\n");
		printf("\033[1;35m [number_of_philosophers] [time_to_die] \033[0m");
		printf("\033[1;35m [time_to_eat] [time_to_sleep] \033[0m");
		printf("\033[1;35m [number_of_meals](optional) \033[0m");
	}
	else if (flag == WRONG_CHARS)
		printf("\033[1;31m Enter only numbers \033[0m");
	else if (flag == WRONG_ARGS)
		printf("\033[1;31m READ THE EVALUATION SHEET CORRECTLY :) \033[0m");
	else if (flag == MUTEX_FAIL)
		printf("\033[1;31m MUTEX FOR FORK FAILED!\033[0m");
	else if (flag == MUTEX_FAIL)
		printf("\033[1;31m MUTEX FOR PRINT FAILED!\033[0m");
	exit(EXIT_FAILURE);
}
