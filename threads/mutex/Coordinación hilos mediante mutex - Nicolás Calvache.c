#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>

#define TRUE 1
#define FALSE 0
#define LIMIT 20
#define SEMAPHORE_NAME "/semaphore"

pthread_mutex_t lock;
pthread_t even_th, odd_th;

int aux = 0;

void *even(void *args);
void *odd(void *args);

int main(int argc, char const *argv[])
{
    pthread_mutex_init(&lock, NULL); //create mutex

    pthread_create(&even_th, NULL, &even, NULL);
    pthread_create(&odd_th, NULL, &odd, NULL);

    pthread_join(even_th, NULL);
    pthread_join(odd_th, NULL);

    pthread_mutex_destroy(&lock);

    return 0;
}

void *even(void *args)
{
    while (aux < LIMIT)
    {
        if ((aux % 2) == 0)
        {
            pthread_mutex_lock(&lock);
            printf("thread 1:%d\n", aux);
            aux = aux + 1;
            pthread_mutex_unlock(&lock);
        }
    }

    return NULL;
}

void *odd(void *args)
{

    while (aux < LIMIT)
    {
        if ((aux % 2) != 0)
        {
            pthread_mutex_lock(&lock);
            printf("thread 2:%d\n", aux);
            aux = aux + 1;
            pthread_mutex_unlock(&lock);
        }
    }

    return NULL;
}
