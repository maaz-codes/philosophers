/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:10:54 by maakhan           #+#    #+#             */
/*   Updated: 2024/10/01 19:54:48 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_number(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

static void check_args(char *argv[])
{
	
	if (ft_atoi(argv[1]) > 200 || ft_atoi(argv[2]) < 60
	 || ft_atoi(argv[3]) < 60 ||  ft_atoi(argv[4]) < 60)
	{
		ft_error(WRONG_ARGS);
	}
}

void parsing(int argc, char *argv[])
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!is_number(argv[i][j]))
				ft_error(WRONG_CHARS);
			j++;
		}
		i++;
	}
	check_args(argv);
}
