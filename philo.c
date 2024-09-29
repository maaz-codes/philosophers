#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void *roll_dice()
{
    int *dice;

    dice = malloc(sizeof(int));
    *dice = (rand() % 6) + 1;
    return ((void *) dice);
}

int main(void)
{
    pthread_t t1;
    int *dice;

    srand(time(NULL));
    pthread_create(&t1, NULL, &roll_dice, NULL);
    pthread_join(t1, (void **) &dice);
    printf("Dice = %i\n", *dice);
}
