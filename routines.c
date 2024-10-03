#include "philo.h"

void eating(t_philo *philo, int index)
{	
	// pthread_mutex_lock(&philo->info->print_locks[index]);
	printf("\033[1;33m %i IS EATING...\n\033[0m", philo->id);
	// pthread_mutex_unlock(&philo->info->print_locks[index]);
	usleep(philo->info->time_to_eat * 10 * 1000);
	philo->info->forks[philo->own_fork] = 0;
	philo->info->forks[philo->other_fork] = 0;
	philo->meal_count += 1;
	if (philo->meal_count == philo->info->max_meals)
		sleep(20); // detach / kill thread ?
}

void sleeping(t_philo *philo, int index)
{	
	// pthread_mutex_lock(&philo->info->print_locks[index]);
	printf("\033[1;35m %i IS SLEEPING...\n\033[0m", philo->id);
	// pthread_mutex_unlock(&philo->info->print_locks[index]);
	usleep(philo->info->time_to_sleep * 10 * 1000);
}

void thinking(t_philo *philo, int index)
{	
	printf("\033[1;32m %i IS THINKING...\n\033[0m", philo->id);
	while (forks_available(philo) == FALSE)
	{
		usleep(1);
	}
	// pthread_mutex_lock(&philo->info->print_locks[index]);
	// pthread_mutex_unlock(&philo->info->print_locks[index]);
}
