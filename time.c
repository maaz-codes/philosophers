#include "philo.h"

long long get_exact_time()
{
    struct timeval tv;
	long long ts;

	gettimeofday(&tv, NULL);
	ts = (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000);
    return (ts);
}

static long get_elapsed_time_microseconds(struct timeval start, struct timeval end)
{
    return (end.tv_sec - start.tv_sec) * 1000000L + (end.tv_usec - start.tv_usec);
}

void precise_usleep(long usec) 
{
    struct timeval start, current;
    long elapsed;
    long rem;

    gettimeofday(&start, NULL);
    do {
        gettimeofday(&current, NULL);
        elapsed = get_elapsed_time_microseconds(start, current);
        rem = usec - elapsed;

        if (rem > 1000)
            usleep(rem / 2);
        
    } while (elapsed < usec);
}

void write_lock(t_info *info, t_philo *philo, char *str, int color)
{
    pthread_mutex_lock(&info->print_lock);
    if (all_alive(info) == FALSE)
    {
        pthread_mutex_unlock(&info->print_lock);
        return ;
    }
    pthread_mutex_lock(&philo->spotlight_lock);
    if (color == RED)
        printf(T_RED "%lld %i %s %i \n" RESET,   get_exact_time() - philo->info->start_program_time,
                                                    philo->id, 
                                                    str,
                                                    philo->spotlight);
    else if (color == GREEN)
        printf(T_GREEN "%lld %i %s %i \n" RESET,   get_exact_time() - philo->info->start_program_time,
                                                    philo->id, 
                                                    str,
                                                    philo->spotlight);
    else if (color == YELLOW)
        printf(T_YELLOW "%lld %i %s %i \n" RESET,   get_exact_time() - philo->info->start_program_time,
                                                    philo->id, 
                                                    str,
                                                    philo->spotlight);
    else if (color == ORANGE)
        printf(T_ORANGE "%lld %i %s %i \n" RESET,   get_exact_time() - philo->info->start_program_time,
                                                    philo->id, 
                                                    str,
                                                    philo->spotlight);
    else if (color == PURPLE)
        printf(T_PURPLE "%lld %i %s %i \n" RESET,   get_exact_time() - philo->info->start_program_time,
                                                    philo->id, 
                                                    str,
                                                    philo->spotlight);
    else if (color == BLUE)
        printf(T_BLUE "%lld %i %s %i \n" RESET,   get_exact_time() - philo->info->start_program_time,
                                                    philo->id, 
                                                    str,
                                                    philo->spotlight);
    pthread_mutex_unlock(&philo->spotlight_lock);
    pthread_mutex_unlock(&info->print_lock);
}
