#include "philo.h"

int all_eating(t_philo *philo)
{
	int flag;

	flag = FALSE;
	pthread_mutex_lock(&philo->info->eat_lock);
	if (philo->info->eating == TRUE)
		flag = TRUE;
	pthread_mutex_unlock(&philo->info->eat_lock);
	return (flag);
}

void rotate_spotlight(t_philo *philo)
{
	pthread_mutex_lock(&philo->spotlight_lock);
	if (philo->spotlight == philo->philo_count)
		philo->spotlight = 1;
	else
		philo->spotlight += 1;
	pthread_mutex_unlock(&philo->spotlight_lock);
}

void mutex_lock(pthread_mutex_t *lock, int *var, int *value)
{
	pthread_mutex_lock(lock);
    var = value;
    pthread_mutex_unlock(lock);
}
