#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>

#define LIMIT 100000000
#define SEMAPHORE_NAME "/semaphore"

pthread_mutex_t lock; //mutex var
pthread_t sum_th, substraction_th;

int shared_var = 0;

void *sum(void *args);
void *substraction(void *args);

int main(int argc, char const *argv[])
{
    pthread_mutex_init(&lock, NULL); //create mutex

    pthread_create(&sum_th, NULL, &sum, NULL);
    pthread_create(&substraction_th, NULL, &substraction, NULL);

    pthread_join(sum_th, NULL);
    pthread_join(substraction_th, NULL);

    printf("shared var is: %d\n", shared_var);

    pthread_mutex_destroy(&lock); //destroy mutex

    return 0;
}

void *sum(void *args)
{
    for (int i = 0; i < LIMIT; i++)
    {
        pthread_mutex_lock(&lock);
        shared_var = shared_var + 1;
        pthread_mutex_unlock(&lock);
    }

    return NULL;
}

void *substraction(void *args)
{
    for (int i = 0; i < LIMIT; i++)
    {
        pthread_mutex_lock(&lock);
        shared_var = shared_var - 1;
        pthread_mutex_unlock(&lock);
    }

    return NULL;
}