#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int nums[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

void *sum(void *arg)
{
    int index = *(int *)arg;
    int sum = 0;
    int i = 0;

    while (i < 5)
    {
        sum += nums[index + i];
        i++;
    }
    *(int *)arg = sum;
    return (arg);
}

int main(void)
{
    pthread_t t[2];
    int i = 0;
    int *a;

    while (i < 2)
    {
        a =  malloc(sizeof(int));
        *a = i * 5;
        if (pthread_create(&t[i], NULL, &sum, (void *)a) != 0)
            return (1);
        i++;
    }
    i = 0;
    int global_sum = 0;
    while (i < 2)
    {
        int *sum;

        if (pthread_join(t[i], (void **)&sum) != 0)
            return (1);
        global_sum += *sum;
        free(sum);
        i++;
    }
    printf("SUM = %i\n", global_sum);
}