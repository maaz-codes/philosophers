#include "philo.h"

static int chairs_available(t_philo *philo)
{
	// malloc the chairs and find the next chair is available or not?
	return (1);
}

static void rotating_chair(t_philo *philo)
{
	while (chairs_available(philo) == FALSE)
	{
		precise_usleep(1);
	}
	if (philo->own_chair == philo->info->philo_count) // last_philo
	{
		philo->own_chair = 1;
	}
	else
	{
		philo->own_chair += 1;
	}
}

void eating(t_philo *philo, int index)
{	
	pthread_mutex_lock(&philo->info->print_locks[index]);
	printf("\033[1;33m %lld %i IS EATING... ON CHAIR: %i\n\033[0m", get_exact_time() - philo->info->start_program_time, philo->id, philo->own_chair);
	// usleep(philo->info->time_to_eat * 1000);
	precise_usleep(philo->info->time_to_eat * 1000);
	philo->info->forks[philo->own_fork] = 0;
	philo->info->forks[philo->other_fork] = 0;
	philo->meal_count += 1;
	rotating_chair(philo);
	if (philo->meal_count == philo->info->max_meals)
		philo->starved = TRUE; // wrong
		// philo->well_fed = TRUE;
	pthread_mutex_unlock(&philo->info->print_locks[index]);
}

void sleeping(t_philo *philo, int index)
{	
	pthread_mutex_lock(&philo->info->print_locks[index]);
	if (philo->info->all_alive == TRUE)
	{
		printf("\033[1;35m %lld %i IS SLEEPING... ON CHAIR: %i\n\033[0m", get_exact_time() - philo->info->start_program_time, philo->id, philo->own_chair);
		// usleep(philo->info->time_to_sleep * 1000);
		precise_usleep(philo->info->time_to_sleep * 1000);
		rotating_chair(philo);
	}
	pthread_mutex_unlock(&philo->info->print_locks[index]);
}

void thinking(t_philo *philo, int index)
{	
	pthread_mutex_lock(&philo->info->print_locks[index]);
	printf("\033[1;32m %lld %i IS THINKING... ON CHAIR: %i\n\033[0m", get_exact_time() - philo->info->start_program_time, philo->id, philo->own_chair);
	while (forks_available(philo) == FALSE)
	{
		// usleep(10);
		precise_usleep(1);
	}
	rotating_chair(philo);
	pthread_mutex_unlock(&philo->info->print_locks[index]);
}
