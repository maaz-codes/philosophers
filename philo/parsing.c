/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:10:54 by maakhan           #+#    #+#             */
/*   Updated: 2024/10/12 17:57:03 by maakhan          ###   ########.fr       */
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
	long long count;
	long long t_die;
	long long t_eat;
	long long t_sleep;
	
	if (!ft_atol_modified(argv[1], &count) || !ft_atol_modified(argv[2], &t_die) 
	|| !ft_atol_modified(argv[3], &t_eat) || !ft_atol_modified(argv[4], &t_sleep))
	{
		ft_error(WRONG_ARGS);
	}
	if (count > 200 || t_die < 60 || t_eat < 60 ||  t_sleep < 60)
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
