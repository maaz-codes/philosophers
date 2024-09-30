#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int shared_value = 0; 

void* increamentor()
{
    int i = 0;
    while (i < 10000)
    {
        shared_value++;
        i++;
    }
}

int main(void)
{
    pthread_t t1;
    pthread_t t2;

    if (pthread_create(&t1, NULL, &increamentor, NULL) != 0)
        return (1);
    if (pthread_create(&t2, NULL, &increamentor, NULL) != 0)
        return (1);
    if (pthread_join(t1, NULL) != 0)
        return (1);
    if (pthread_join(t2, NULL) != 0)
        return (1);
    printf("shared_value = %i\n", shared_value);
    return (0);
}