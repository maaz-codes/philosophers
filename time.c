#include "philo.h"

long long get_exact_time()
{
    struct timeval tv;
	long long ts;

	gettimeofday(&tv, NULL);
	ts = (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000);
    return (ts);
}
