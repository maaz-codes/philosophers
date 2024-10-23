/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:10:54 by maakhan           #+#    #+#             */
/*   Updated: 2024/10/23 14:48:26 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	is_number(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

static void	check_args(char *argv[], int argc)
{
	long long	count;
	long long	t_die;
	long long	t_eat;
	long long	t_sleep;
	long long	meals;

	if (!ft_atol_modified(argv[1], &count) || !ft_atol_modified(argv[2], &t_die)
		|| !ft_atol_modified(argv[3], &t_eat) || !ft_atol_modified(argv[4],
			&t_sleep))
	{
		ft_error(WRONG_ARGS);
	}
	if (count > 200 || t_die < 60 || t_eat < 60 || t_sleep < 60)
	{
		ft_error(WRONG_ARGS);
	}
	if (argc == 6)
	{
		if (!ft_atol_modified(argv[5], &meals))
			ft_error(WRONG_ARGS);
		if (meals < 0)
			ft_error(WRONG_ARGS);
		if (meals == 0)
			exit(EXIT_SUCCESS);
	}
}

void	parsing(int argc, char *argv[])
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
	check_args(argv, argc);
}
