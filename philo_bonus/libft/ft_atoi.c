/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 18:43:57 by maakhan           #+#    #+#             */
/*   Updated: 2024/10/14 09:51:15 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

char	*ft_atol_modified(char *str, long long *n)
{
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	*n = 0;
	while (str[i] != '\0' && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '+' || str[0] == '-')
		if (str[i++] == '-')
			sign = -1;
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			*n = (*n * 10) + (str[i] - '0');
			if ((*n > INT_MAX && sign == 1) || (sign == -1 && *n > 2147483648))
				return (NULL);
		}
		else
			return (NULL);
		i++;
	}
	*n *= sign;
	return ("Success");
}

int	ft_atoi(const char *str)
{
	int					i;
	int					sign;
	unsigned long long	number;

	i = 0;
	sign = 1;
	number = 0;
	while (str[i] != '\0' && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
	{
		number = (number * 10) + (str[i] - '0');
		if (number > LLONG_MAX && sign == -1)
			return (0);
		if (number > LLONG_MAX)
			return (-1);
		i++;
	}
	return (number * sign);
}
