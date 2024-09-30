#include "philo.h"

void check_args(t_philos_info philo_info)
{
	if (philo_info.philo_count > 200 || philo_info.time_to_die < 60
	 || philo_info.time_to_eat < 60 || philo_info.time_to_sleep < 60)
	{
		colored_printf("READ THE EVALUATION SHEET CORRECTLY :)", RED);
		exit(1);
	}
}

void eating()
{
	usleep(5 * 1000 * 1000);
}

void sleeping()
{
	usleep(5 * 1000 * 1000);
}

void thinking()
{
	usleep(5 * 1000 * 1000);
}

void	philosophers_init(char *argv[], t_philos_info *philo_info)
{
	int	i;

	i = 0;
	philo_info->philo_count = ft_atoi(argv[1]);
	philo_info->time_to_die = ft_atoi(argv[2]);
	philo_info->time_to_eat = ft_atoi(argv[3]);
	philo_info->time_to_sleep = ft_atoi(argv[4]);
	check_args(*philo_info);
	while (i < philo_info->philo_count)
	{
		philo_info->philo[i].id = i + 1;
		philo_info->philo[i].has_forks = 0;
		i++;
	}
	i = 0;
	while (i < philo_info->philo_count)
	{
		philo_info->fork[i].taken = 0;
		i++;
	}
	// pthread_mutex_init(&philo_info->mutex, NULL);
}

void *routine(void *args)
{
	t_philo *philo;
	struct timeval tv;
	long long ts;

	philo = (t_philo *)args;
	gettimeofday(&tv, NULL);
	ts = (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000);
	printf("\033[1;36m %lld PHILOSOPHER %i SEATED!\033[0m\n", ts, philo->id);
	sleep(3);
	return(args);
}

void dinning_table(t_philos_info *philo_info)
{
	pthread_t t[200];
	int i;

	i = 0;
	while (i < philo_info->philo_count)
	{
		pthread_create(&t[i], NULL, &routine, (void *)&philo_info->philo[i]);
		i++;
	}
	i = 0;
	while (i < philo_info->philo_count)
	{
		pthread_join(t[i], NULL);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_philos_info	philo_info;

	if (argc == 5 || argc == 6)
	{
		parsing(argc, argv);
		philosophers_init(argv, &philo_info);
		dinning_table(&philo_info);
		// pthread_mutex_destroy(&philo_info.mutex);
		return (0);
	}
	ft_error('n');
}
