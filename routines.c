#include "philo.h"

static void rotate_spotlight(t_philo *philo)
{
	if (philo->spotlight == philo->info->philo_count)
		philo->spotlight = 1;
	else
		philo->spotlight += 1;
}

void eating(t_philo *philo, int index)
{	
	if (philo->info->all_alive == TRUE)
	{
		write_lock(philo, "IS EATING... ON SPOTLIGHT:", YELLOW);
		precise_usleep(philo->info->time_to_eat * 1000);

		pthread_mutex_lock(&philo->info->fork_locks[philo->own_fork]);
		pthread_mutex_lock(&philo->info->fork_locks[philo->other_fork]);
		philo->info->forks[philo->own_fork] = 0;
		philo->info->forks[philo->other_fork] = 0;
		pthread_mutex_unlock(&philo->info->fork_locks[philo->own_fork]);
		pthread_mutex_unlock(&philo->info->fork_locks[philo->other_fork]);

		philo->meal_count += 1;
		rotate_spotlight(philo);
	}
	// printf("\033[1;33m %lld %i  %i\n\033[0m", get_exact_time() - philo->info->start_program_time, philo->id, philo->spotlight);
}

void sleeping(t_philo *philo, int index)
{	
	if (philo->info->all_alive == TRUE)
	{
		write_lock(philo, "IS SLEEPING... ON SPOTLIGHT:", PURPLE);
		precise_usleep(philo->info->time_to_sleep * 1000);
		rotate_spotlight(philo);
	}
	// printf("\033[1;35m %lld %i  %i\n\033[0m", get_exact_time() - philo->info->start_program_time, philo->id, philo->spotlight);
}

void thinking(t_philo *philo, int index)
{	
	write_lock(philo, "IS THINKING... ON SPOTLIGHT:", GREEN);
	precise_usleep(100);
	while (forks_available(philo) == FALSE && philo->info->all_alive == TRUE)
	{
		precise_usleep(1);
	}
	rotate_spotlight(philo);
	// printf("\033[1;32m %lld %i  %i\n\033[0m", get_exact_time() - philo->info->start_program_time, philo->id, philo->spotlight);
}
