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
    pthread_t t[4];
    int i = 0;
    
    while (i < 4)
    {
        printf("Thread %i has been created.\n", i);
        if (pthread_create(&t[i], NULL, &increamentor, NULL) != 0)
            return (1);
        i++;
    }
    i = 0;
    while (i < 4)
    {
        printf("Thread %i has been destroyed\n", i);
        if (pthread_join(t[i], NULL) != 0)
            return (1);
        i++;
    }
    return (0);
}