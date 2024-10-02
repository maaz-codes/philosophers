/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:06:04 by maakhan           #+#    #+#             */
/*   Updated: 2024/10/02 22:11:13 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// == RED ==
// \033[1;31m {TEXT} \033[0m

// == GREEN ==
// \033[1;32m {TEXT} \033[0m

// == YELLOW ==
// \033[1;33m {TEXT} \033[0m

// == ORANGE ==
// \033[1;34m {TEXT} \033[0m

// == PURPLE ==
// \033[1;35m {TEXT} \033[0m

// == BLUE ==
// \033[1;36m {TEXT} \033[0m

// == WHITE ==
// \033[1;36m {TEXT} \033[0m

// void	colored_printf(char *str, char *color)
// {
// 	if (ft_strncmp(color, RED, ft_strlen(RED)) == 0)
// 		printf("\033[1;31m %s \033[0m", str);
// 	else if (ft_strncmp(color, GREEN, ft_strlen(GREEN)) == 0)
// 		printf("\033[1;32m %s \033[0m", str);
// 	else if (ft_strncmp(color, YELLOW, ft_strlen(YELLOW)) == 0)
// 		printf("\033[1;33m %s \033[0m", str);
// 	else if (ft_strncmp(color, ORANGE, ft_strlen(ORANGE)) == 0)
// 		printf("\033[1;34m %s \033[0m", str);
// 	else if (ft_strncmp(color, PURPLE, ft_strlen(PURPLE)) == 0)
// 		printf("\033[1;35m %s \033[0m", str);
// 	else if (ft_strncmp(color, BLUE, ft_strlen(BLUE)) == 0)
// 		printf("\033[1;36m %s \033[0m", str);
// 	else
// 		printf("\033[1;37m %s \033[0m", str);
// }

// void free_array(int *array)
// {
// 	int i ;

// 	i = 0;
// 	while (array[i])
// 	{
// 		free(array[i]);
// 		i++;
// 	}
// 	free(array);
// }

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
	else if (flag == MUTEX_F)
		printf("\033[1;31m MUTEX FOR FORK FAILED!\033[0m");
	else if (flag == MUTEX_P)
		printf("\033[1;31m MUTEX FOR PRINT FAILED!\033[0m");
	exit(EXIT_FAILURE);
}
