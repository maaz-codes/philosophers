/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:49:01 by maakhan           #+#    #+#             */
/*   Updated: 2024/10/23 17:09:24 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

// colors
# define RED 2001
# define GREEN 2002
# define YELLOW 2003
# define ORANGE 2004
# define PURPLE 2005
# define BLUE 2006
# define WHITE 2007

// printing_coolors
# define T_RED "\033[1;31m"
# define T_GREEN "\033[1;32m"
# define T_YELLOW "\033[1;33m"
# define T_ORANGE "\033[1;34m"
# define T_PURPLE "\033[1;35m"
# define T_BLUE "\033[1;36m"
# define T_WHITE "\033[1;37m"
# define RESET "\033[0m"

// named_semaphores
# define SEMA_WRITE "/sema_write"
# define SEMA_LIGHT "/sema_light"
# define SEMA_THINK "/sema_think"
# define SEMA_DEATH "/sema_death"
# define SEMA_FORKS "/sema_forks"
# define SEMA_MEALS "/sema_meals"

// general
# define MAX_PHILOS 200
# define TRUE 1
# define FALSE 0
# define EXIT_FAILURE 1
# define EXIT_SUCCESS 0
# define ON 1
# define OFF 0

// error_flags
# define WRONG_FORMAT 1001
# define WRONG_CHARS 1002
# define WRONG_ARGS 1003
# define FORK_FAIL 1005
# define THREAD_FAIL 1006
# define SEMA_FAIL 1007

typedef struct s_info
{
	long long	start_program_time;
	int			philo_count;
	int			all_alive;
	int			eating;
	int			all_full;
	int			dinner_ended;
	int			forks[MAX_PHILOS];
	sem_t		*sema_think;
	sem_t		*sema_light;
	sem_t		*sema_write;
	sem_t		*sema_death;
	sem_t		*sema_forks;
	sem_t		*sema_meals;
}				t_info;

typedef struct s_philo
{
	t_info		*info;
	int			id;
	int			spotlight;
	int			own_fork;
	int			other_fork;
	int			philo_count;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			max_meals;
	int			meal_count;
	int			statiated;
	int			is_dead;
	int			leader;
	int			slept;
	long long	start_time;
	pthread_t	reaper;
}				t_philo;

// helpers
int				ft_atoi(const char *str);
char			*ft_atol_modified(char *str, long long *n);
char			**ft_split(const char *s, char c);
size_t			ft_strlen(const char *str);

// parsing.c
void			parsing(int argc, char *argv[]);

// init.c
void			init_info(char *argv[], t_info *info);
void			init_philos(char **argv, t_philo *philo, t_info *info);

// errors.c
void			ft_error(int flag);
void			create_thread(pthread_t *t, void *(*routine)(void *),
					void *args);
void			join_thread(pthread_t *t);
sem_t			*open_sem(char *name, int value);

// routines.c
int				eating(t_info *info, t_philo *philo);
int				sleeping(t_info *info, t_philo *philo);
int				thinking(t_info *info, t_philo *philo);

// time.c
long long		get_exact_time(void);
int				precise_usleep(long usec, t_philo *philo);

// utils.c
void			write_sema(t_info *info, t_philo *philo, char *str);
int				all_alive(t_philo *philo);
int				all_full(t_philo *philo);
int				spotlight(t_philo *philo);
void			rotate_spotlight(t_philo *philo);

// semaphores.c
void			release_thinkers(t_info *info, t_philo *philo);
void			waiting(t_info *info);
void			sema_close(t_info *info);
void			sema_unlink(t_info *info);

// dinning.c
void			dinning(t_philo *philo, t_info *info);
void			*kitchen(void *args);
void			massacre(t_philo *philo);
void			*graveyard(void *args);

#endif