#include "philo_bonus.h"

void write_sema(t_info *info, t_philo *philo, char *str)
{
	sem_wait(info->sema_write);
	if (info->all_alive == TRUE && info->all_full == FALSE)
		printf("%lld %i %s on light %i\n", get_exact_time() - info->start_program_time, philo->id, str, philo->spotlight);
	sem_post(info->sema_write);
}

int all_alive(t_philo *philo)
{	
	if (get_exact_time() - philo->start_time > philo->time_to_die)
	{
		philo->info->all_alive = FALSE;
		philo->leader = TRUE;
		return (FALSE);
	}
	return (TRUE);
}

int all_full(t_philo *philo)
{
	if (philo->statiated == TRUE)
		return (TRUE);
	return (FALSE);
}

void release_thinkers(t_info *info, t_philo *philo)
{
	int  i;

	if (philo->leader == TRUE)
	{
		i = 0;
		while (i < philo->philo_count)
		{
			sem_post(info->sema_think);
			i++;
		}
		return ;
	}
	if (philo->spotlight == 2 && philo->philo_count % 2 != 0) 
		sem_post(info->sema_think);
	sem_post(info->sema_think);
} 

int	spotlight(t_philo *philo)
{
	int flag;

	flag = OFF;
	if(philo->spotlight % 2 == 0)
		flag = ON;
	return (flag);
}

void rotate_spotlight(t_philo *philo)
{
	if (philo->spotlight == philo->philo_count)
		philo->spotlight = 1;
	else
		philo->spotlight += 1;
}

// int check_all_alive(t_philo *philo)
// {
// 	int flag;

// 	flag = TRUE;
// 	sem_wait(philo->info->sema_alive);
// 	if (philo->info->all_alive == FALSE)
// 		flag = FALSE;
// 	sem_post(philo->info->sema_alive);
// 	return (flag);
// }

// int check_all_full(t_philo *philo)
// {
// 	int flag;

// 	flag = FALSE;
// 	sem_wait(philo->info->sema_all_full);
// 	if (philo->info->all_full == TRUE)
// 		flag = TRUE;
// 	sem_post(philo->info->sema_all_full);
// 	return (flag);
// }
