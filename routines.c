#include "philo.h"

void sleeping(t_philo *philo)
{
	struct timeval tv;
	long long ts;

	gettimeofday(&tv, NULL);
	ts = (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000);
	printf("\033[1;35m %lld PHILOSOPHER %i is SLEEPING \033[0m\n", ts, philo->id);
	usleep(5 * 1000 * 1000);
}

void eating()
{
	usleep(5 * 1000 * 1000);
}

void thinking()
{
	usleep(5 * 1000 * 1000);
}
