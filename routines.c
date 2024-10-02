#include "philo.h"

void eating(t_philo *philo, int index)
{	
	// pthread_mutex_lock(&philo->info->print_locks[index]);
	printf("\033[1;33m %i IS EATING...\n\033[0m", philo->id);
	// pthread_mutex_unlock(&philo->info->print_locks[index]);
	usleep(philo->info->time_to_eat * 100 * 1000);
}

void sleeping(t_philo *philo, int index)
{	
	// pthread_mutex_lock(&philo->info->print_locks[index]);
	printf("\033[1;35m %i IS SLEEPING...\n\033[0m", philo->id);
	// pthread_mutex_unlock(&philo->info->print_locks[index]);
	usleep(philo->info->time_to_sleep * 100 * 1000);
}

void thinking(t_philo *philo, int index)
{	
	// pthread_mutex_lock(&philo->info->print_locks[index]);
	printf("\033[1;32m %i IS THINKING...\n\033[0m", philo->id);
	// pthread_mutex_unlock(&philo->info->print_locks[index]);
	usleep(philo->info->time_to_sleep * 100 * 1000);
}
