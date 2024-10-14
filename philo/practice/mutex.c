#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int shared_value = 0;
pthread_mutex_t mutex;

void* increamentor()
{
    int i = 0;
    while (i < 10000)
    {   
        pthread_mutex_lock(&mutex);
        shared_value++;
        pthread_mutex_unlock(&mutex);
        i++;
    }
}

int main(void)
{
    pthread_t t1;
    pthread_t t2;

    pthread_mutex_init(&mutex, NULL);
    if (pthread_create(&t1, NULL, &increamentor, NULL) != 0)
        return (1);
    if (pthread_create(&t2, NULL, &increamentor, NULL) != 0)
        return (1);
    if (pthread_join(t1, NULL) != 0)
        return (1);
    if (pthread_join(t2, NULL) != 0)
        return (1);
    printf("shared_value = %i\n", shared_value);
    pthread_mutex_destroy(&mutex);
    return (0);
}