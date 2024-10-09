#include "philo.h"

void print_forks(t_philo *philo)
{
	int i = 0;

	while (i < philo->info->philo_count)
	{
		printf("%i, ", philo->info->forks[i]);
		i++;
	}
}

int forks_available(t_philo *philo)
{
	int own_fork; 
	int other_fork;

	pthread_mutex_lock(&philo->info->fork_locks[philo->own_fork]);
	pthread_mutex_lock(&philo->info->fork_locks[philo->other_fork]);
	own_fork = philo->info->forks[philo->own_fork];
	other_fork = philo->info->forks[philo->other_fork];
	pthread_mutex_unlock(&philo->info->fork_locks[philo->own_fork]);
	pthread_mutex_unlock(&philo->info->fork_locks[philo->other_fork]);
	return (own_fork == 0 && other_fork == 0);
}

int spotlight(t_philo *philo)
{
	return (philo->spotlight % 2 == 0);
}

int all_alive(t_philo *philo)
{
	pthread_mutex_t lock;
	int flag;

	flag = FALSE;
	pthread_mutex_init(&lock, NULL);
	pthread_mutex_lock(&lock);
	if (philo->info->all_alive == TRUE)
		flag = TRUE;
	pthread_mutex_unlock(&lock);
	pthread_mutex_destroy(&lock);
	return (flag);
}

void *dinning_table(void *args)
{
	t_philo *philo;

	philo = (t_philo *)args;
	while (all_alive == TRUE)
	{	
		if (spotlight(philo) == ON)             
		{
			while (forks_available(philo) == FALSE)
			{
				precise_usleep(1);
			}
			write_lock(philo, "HAS TAKEN FORKS ON SPOTLIGHT:", ORANGE);

			pthread_mutex_lock(&philo->info->fork_locks[philo->own_fork]);
			pthread_mutex_lock(&philo->info->fork_locks[philo->other_fork]);
			philo->info->forks[philo->own_fork] = philo->id;
			philo->info->forks[philo->other_fork] = philo->id;
			print_forks(philo);
			pthread_mutex_unlock(&philo->info->fork_locks[philo->own_fork]);
			pthread_mutex_unlock(&philo->info->fork_locks[philo->other_fork]);
			eating(philo, philo->id - 1);
			philo->start_time = get_exact_time(); // reset_time
			sleeping(philo, philo->id - 1);
		}
		else	
		{
			// print_chairs(philo);
			thinking(philo, philo->id - 1);
		}
	}
	// pthread_mutex_unlock(&philo->info->fork_locks[philo->own_fork]);
	// pthread_mutex_unlock(&philo->info->fork_locks[philo->other_fork]);
	return (args);
}

void join_and_destroy(pthread_t *t, t_info *info, pthread_mutex_t *fork_locks, pthread_mutex_t *print_locks)
{
	int i;
	
	i = 0;
	while (i < info->philo_count)
	{
		pthread_join(t[i], NULL);
		i++;
	}
	i = 0;
	while (i < info->philo_count)
	{
		pthread_mutex_destroy(&fork_locks[i]);
		pthread_mutex_destroy(&print_locks[i]);
		printf("%i, ", info->forks[i]);
		i++;
	}
}