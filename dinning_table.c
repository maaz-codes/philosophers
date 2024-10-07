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

	own_fork = philo->info->forks[philo->own_fork];
	other_fork = philo->info->forks[philo->other_fork];
	if (own_fork == 0 && other_fork == 0)
		return (1);
	else
		return (0);
}

void *dinning_table(void *args)
{
	t_philo *philo;

	philo = (t_philo *)args;
	philo->start_time = get_exact_time();
	pthread_mutex_lock(&philo->info->fork_locks[philo->id - 1]);
	while (philo->info->all_alive == TRUE)
	{	
		if (philo->own_chair % 2 == 0)                
		{
			philo->info->forks[philo->own_fork] = philo->id;
			philo->info->forks[philo->other_fork] = philo->id;
			// printf("\033[1;34m %lld %i HAS TAKEN FORKS ON CHAIR: %i \033[0m\n", get_exact_time() - philo->info->start_program_time, philo->id, philo->own_chair);
			// print_forks(philo);
			eating(philo, philo->id - 1);
			philo->start_time = get_exact_time(); // reset_time
			sleeping(philo, philo->id - 1);
		}
		else	
			thinking(philo, philo->id - 1);
		// if (forks_available(philo) == TRUE)
		// {
		// 	philo->info->forks[philo->own_fork] = philo->id;
		// 	philo->info->forks[philo->other_fork] = philo->id;
		// 	printf("\033[1;34m %lld %i HAS TAKEN FORKS \033[0m\n", get_exact_time() - philo->info->start_program_time, philo->id);
		// 	eating(philo, philo->id - 1);
		// 	philo->start_time = get_exact_time();
		// 	sleeping(philo, philo->id - 1);
		// }
		// else
		// 	thinking(philo, philo->id - 1);
	}
	pthread_mutex_unlock(&philo->info->fork_locks[philo->id - 1]);
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
		// printf("%i, ", info->chairs[i]);
		printf("%i, ", info->forks[i]);
		i++;
	}
}
