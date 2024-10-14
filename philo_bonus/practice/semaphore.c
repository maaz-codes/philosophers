#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

# define SEM_NAME "/my_sema"

void print(sem_t *sema, int id)
{
    sem_wait(sema);
    printf("Process %i has arrived\n", id);
    sleep(1);
    sem_post(sema);
}

int main(void)
{
    sem_t *semaphore = sem_open(SEM_NAME, O_CREAT, 0644, 3);
    if (semaphore == SEM_FAILED)
        printf("semaphore failed to open\n");
    int i = 0;
    while (i < 3)
    {
        pid_t pid = fork();
        if (pid == -1)
            printf("Error in fork()-ing\n");
        if (pid == 0)
        {
            print(semaphore, i + 1);
            sem_close(semaphore);
            exit(0);
        }
        i++;
    }
    i = 0;
    while (i < 3)
    {
        wait(NULL);
        i++;
    }
    sem_close(semaphore);
    sem_unlink(SEM_NAME);
}