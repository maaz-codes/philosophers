/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:06:04 by maakhan           #+#    #+#             */
/*   Updated: 2024/09/30 11:45:58 by maakhan          ###   ########.fr       */
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

void	colored_printf(char *str, char *color)
{
	if (ft_strncmp(color, RED, ft_strlen(RED)) == 0)
		printf("\033[1;31m %s \033[0m", str);
	else if (ft_strncmp(color, GREEN, ft_strlen(GREEN)) == 0)
		printf("\033[1;32m %s \033[0m", str);
	else if (ft_strncmp(color, YELLOW, ft_strlen(YELLOW)) == 0)
		printf("\033[1;33m %s \033[0m", str);
	else if (ft_strncmp(color, ORANGE, ft_strlen(ORANGE)) == 0)
		printf("\033[1;34m %s \033[0m", str);
	else if (ft_strncmp(color, PURPLE, ft_strlen(PURPLE)) == 0)
		printf("\033[1;35m %s \033[0m", str);
	else if (ft_strncmp(color, BLUE, ft_strlen(BLUE)) == 0)
		printf("\033[1;36m %s \033[0m", str);
	else
		printf("\033[1;37m %s \033[0m", str);
}

void	ft_error(char flag)
{
	if (flag == 'n')
	{
		colored_printf("Enter 4 or 5 args\n", RED);
		colored_printf("[number_of_philosophers] [time_to_die]", PURPLE);
		colored_printf("[time_to_eat] [time_to_sleep]", PURPLE);
		colored_printf("[number_of_meals](optional)", PURPLE);
	}
	else
		colored_printf("Enter only numbers", RED);
	exit(EXIT_FAILURE);
}
