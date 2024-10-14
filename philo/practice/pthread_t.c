#include "philo.h"
#include <string.h>

int fuel = 0;
pthread_mutex_t fuel_lock;
pthread_mutex_t car_lock;

void *fueling(void *args)
{
    pthread_mutex_lock(&fuel_lock);
    while (fuel < 50)
    {
        printf("Fueling...\n");
        fuel += 15;
        printf("Fuel = %i\n", fuel);
        sleep(1);
    }
    pthread_mutex_unlock(&fuel_lock);

    return (args);
}

void *car(void *args)
{
    pthread_mutex_lock(&car_lock);
    if (fuel < 40)
        printf("Waiting...\n");
    while (fuel < 40)
    {
        pthread_mutex_unlock(&car_lock);
    }
    printf("Filling gas...\n");
    fuel -= 40;
    printf("Fuel = %i\n", fuel);
    sleep(1);
    pthread_mutex_unlock(&car_lock);

    return(args);
}

int main(int argc, char **argv, char **env)
{
    pthread_t t[2];

    pthread_mutex_init(&fuel_lock, NULL);
    pthread_mutex_init(&car_lock, NULL);
    pthread_create(&t[1], NULL, &car, NULL);    
    pthread_create(&t[0], NULL, &fueling, NULL);
    
    int i = 0;
    while (i < 2)
    {
        pthread_join(t[i], NULL);
        i++;
    }
    pthread_mutex_destroy(&fuel_lock);
    pthread_mutex_destroy(&car_lock);
}
