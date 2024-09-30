/*
    --THE PROBLEM--
    Create 10 threads, each taking
    a unique prime from the primes
    array and prints it on the screen.
*/

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void *priming(void *arg)
{
    int index = *(int *)arg;

    free(arg);
    return ((void *)&primes[index]);
}

int main(void)
{
    pthread_t t[10];
    int i = 0;
    int *prime;

    while (i < 10)
    {
        int *a = malloc(sizeof(int));
        *a = i;
        pthread_create(&t[i], NULL, &priming, (void *)a);
        i++;
    }
    i = 0;
    while (i < 10)
    {
        pthread_join(t[i], (void **) &prime);
        printf("%i, ", *prime);
        i++;
    }
}
