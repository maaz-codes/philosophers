/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:49:01 by maakhan           #+#    #+#             */
/*   Updated: 2024/09/30 16:44:39 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
#include <sys/time.h>

// COLORS
# define RED "RED"
# define GREEN "GREEN"
# define YELLOW "YELLOW"
# define ORANGE "ORANGE"
# define PURPLE "PURPLE"
# define BLUE "BLUE"
# define WHITE "WHITE"

typedef struct	s_fork
{
	int taken;
}				t_fork;				

typedef struct 	s_philo
{
	int id;
	int has_forks;
}				t_philo;

typedef struct 	s_philos_info
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meal_count;
	int 			fork_count;
	t_philo			philo[200];
	t_fork			fork[200];
	pthread_mutex_t	mutex;
}					t_philos_info;

// libft
int					ft_atoi(const char *str);
char				**ft_split(const char *s, char c);
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlen(const char *str);
int					ft_strncmp(const char *s1, const char *s2, size_t n);

// parsing
int					parsing(int argc, char *argv[]);

// errors
void				ft_error(char flag);
void				colored_printf(char *str, char *color);

#endif