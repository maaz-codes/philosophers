#include "philo_bonus.h"

void write_sema(t_info *info, t_philo *philo, char *str)
{
    sem_wait(info->sema_write);
    printf("%lld %i %s on light %i\n", get_exact_time() - info->start_program_time, philo->id, str, philo->spotlight);
    sem_post(info->sema_write);
}