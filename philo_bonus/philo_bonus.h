/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:49:01 by maakhan           #+#    #+#             */
/*   Updated: 2024/10/14 22:08:23 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/wait.h>

# define SEMA_PHILO "/philosophers"
# define SEMA_LIGHT "/sema_light"
# define SEMA_WRITE "/sema_write"

// COLORS
# define RED 	2001
# define GREEN 	2002
# define YELLOW 2003
# define ORANGE 2004
# define PURPLE 2005
# define BLUE 	2006
# define WHITE 	2007

# define T_RED	 		"\033[1;31m"
# define T_GREEN 		"\033[1;32m"
# define T_YELLOW 		"\033[1;33m"
# define T_ORANGE 		"\033[1;34m"
# define T_PURPLE 		"\033[1;35m"
# define T_BLUE 		"\033[1;36m"
# define T_WHITE 		"\033[1;37m"
# define RESET 			"\033[0m"

// general
# define MAX_PHILOS 	200
# define TRUE  			1
# define FALSE			0
# define EXIT_FAILURE 	1
# define EXIT_SUCCESS 	0
# define ON			 	1
# define OFF		 	0

// error flags
# define WRONG_FORMAT	1001
# define WRONG_CHARS	1002
# define WRONG_ARGS		1003
# define MUTEX_FAIL		1004

typedef struct s_info
{
	long long		start_program_time;
	int				philo_count;
	int 			all_alive;
	int				eating;
	int				meals_done;
	int				forks[MAX_PHILOS];
	pthread_mutex_t fork_locks[MAX_PHILOS]; 
	pthread_mutex_t print_lock;
	pthread_mutex_t eat_lock;
	pthread_mutex_t alive_lock;
	pthread_mutex_t	reset_lock[MAX_PHILOS];
}					t_info;

typedef struct s_philo
{
	t_info			*info;
	int				id;
	int				spotlight;
	int				own_fork;
	int				other_fork;
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_meals;
	int				meal_count;
	int				statiated;
	long long		start_time;
	pthread_t		t[MAX_PHILOS];
	pthread_mutex_t spotlight_lock;
	pthread_mutex_t meal_lock;
}					t_philo;

typedef struct s_doctor
{
	t_info 			*info;
	t_philo			*philo;
	int				philo_count;
	int				time_to_die;
}					t_doctor;

typedef struct s_sema
{
	sem_t			*sema_philo;
	sem_t 			*sema_light;
	sem_t			*sema_write;
}					t_sema;

// libft
int					ft_atoi(const char *str);
char				*ft_atol_modified(char *str, long long *n);
char				**ft_split(const char *s, char c);
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlen(const char *str);
int					ft_strncmp(const char *s1, const char *s2, size_t n);

// parsing
void				parsing(int argc, char *argv[]);

// init
void				init_info(char *argv[], t_info *info);
void 				init_philos(char **argv, t_philo *philo, t_info *info);
void 				init_doctor(t_doctor *doctor, t_info *info, t_philo *philo);
void 				init_mutexes(t_info *info, t_philo *philo);

// errors
void				ft_error(int flag);

// routines
// void 				eating(t_philo *philo, int index);
// void				sleeping(t_philo *philo, int index);
// void 				thinking(t_philo *philo, int index);

// dinning_table
void 				*dinning_table(void *args);
int 				forks_available(t_philo *philo);
int					spotlight(t_philo *philo, t_sema *sema);

// time
long long 			get_exact_time();
void 				precise_usleep(t_info *info, long usec);
void 				write_lock(t_info *info, t_philo *philo, char *str, int color);
void 				write_sema(t_info *info, t_philo *philo, char *str, t_sema *sema);

// checkup
// void 				*checkup(void *args);
// int 				is_dead(t_doctor *doctor, int i);
// int 				all_ate(t_doctor *doctor, int i, int *count);

// utils
int 				all_eating(t_philo *philo);
void 				rotate_spotlight(t_philo *philo);
void 				mutex_lock(pthread_mutex_t *lock, int *var, int value);
int 				all_alive(t_info *info);

#endif