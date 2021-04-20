#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>

#define LIMIT 1000000
#define SEMAPHORE_NAME "/semaphore"

sem_t *semaphore;
pthread_t sum_th, substraction_th;

int shared_var = 0;

void *sum(void *args);
void *substraction(void *args);

int main(int argc, char const *argv[])
{
    semaphore = sem_open(SEMAPHORE_NAME, O_CREAT, S_IRUSR | S_IWUSR, 1);

    pthread_create(&sum_th, NULL, &sum, NULL);
    pthread_create(&substraction_th, NULL, &substraction, NULL);

    pthread_join(sum_th, NULL);
    pthread_join(substraction_th, NULL);

    sem_close(semaphore);
    sem_unlink(SEMAPHORE_NAME);

    printf("shared var is: %d\n", shared_var);
    return 0;
}

void *sum(void *args)
{
    for (int i = 0; i < LIMIT; i++)
    {
        sem_wait(semaphore);
        shared_var = shared_var + 1;
        sem_post(semaphore);
    }

    return NULL;
}

void *substraction(void *args)
{
    for (int i = 0; i < LIMIT; i++)
    {
        sem_wait(semaphore);
        shared_var = shared_var - 1;
        sem_post(semaphore);
    }

    return NULL;
}