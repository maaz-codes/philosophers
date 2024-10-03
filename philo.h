/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:49:01 by maakhan           #+#    #+#             */
/*   Updated: 2024/10/03 07:18:35 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

// COLORS
# define RED "RED"
# define GREEN "GREEN"
# define YELLOW "YELLOW"
# define ORANGE "ORANGE"
# define PURPLE "PURPLE"
# define BLUE "BLUE"
# define WHITE "WHITE"

// general
# define MAX_PHILOS 	200
# define TRUE  			1
# define FALSE			0
# define EXIT_FAILURE 	1
# define EXIT_SUCCESS 	0

// error flags
# define WRONG_FORMAT	1001
# define WRONG_CHARS	1002
# define WRONG_ARGS		1003
# define MUTEX_F		1004
# define MUTEX_P		1005

typedef struct s_info
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_meals;
	int 			*forks;
	pthread_mutex_t	*fork_locks;
	pthread_mutex_t	*print_locks;
	int 			all_alive;
}					t_info;

typedef struct s_philo
{
	t_info			*info;
	int				id;
	int				own_fork;
	int				other_fork;
	int				meal_count;
	long long       last_meal_time;
	pthread_t		thread;
}					t_philo;

// libft
int					ft_atoi(const char *str);
char				**ft_split(const char *s, char c);
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlen(const char *str);
int					ft_strncmp(const char *s1, const char *s2, size_t n);

// parsing
void				parsing(int argc, char *argv[]);

// errors
void				ft_error(int flag);
// void 				free_array(int *array);

// init
void				init_info(char *argv[], t_info *info, pthread_mutex_t *fork_locks, pthread_mutex_t *print_locks);
void 				init_philo(char **argv, t_philo *philo, t_info *info, int index);

// routines
void 				eating(t_philo *philo, int index);
void				sleeping(t_philo *philo, int index);
void 				thinking(t_philo *philo, int index);

// dinning_table
int 				forks_available(t_philo *philo);
void 				*dinning_table(void *args);
void 				join_and_destroy(pthread_t *t, t_info *info, pthread_mutex_t *fork_locks, pthread_mutex_t *print_locks);

#endif