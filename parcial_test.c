#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define MILLON 1000000
#define ARRAYSIZE 5
#define PAR 0
#define IMPAR 1

int arr[ARRAYSIZE], i = 0, FLAG_EXIT = 1, FLAG_PARIDAD = -1, counter = 0;

pthread_t pares_t, impares_t, master_t;
pthread_mutex_t lock;

void *pares_f(void *parm);
void *impares_f(void *parm);
void *master_f(void *parm);

unsigned int aleatorio_intervalo(unsigned int min, unsigned int max);

int main()
{
    pthread_mutex_init(&lock, NULL);

    pthread_create(&master_t, NULL, master_f, NULL);
    pthread_create(&pares_t, NULL, pares_f, NULL);
    pthread_create(&impares_t, NULL, impares_f, NULL);

    pthread_join(pares_t, NULL);
    pthread_join(impares_t, NULL);
    pthread_join(master_t, NULL);

    printf("\ncounter: %d\n", counter);

    pthread_mutex_destroy(&lock);

    return 0;
}

void *master_f(void *parm)
{
    while (i < ARRAYSIZE)
    {

        FLAG_PARIDAD = i % 2;
        usleep(10000);

        pthread_mutex_lock(&lock);
        i = i + 1;
        pthread_mutex_unlock(&lock);
    }

    i = 0;

    FLAG_EXIT = 0;
}

void *pares_f(void *parm)
{
    while (FLAG_EXIT)
    {
        while (FLAG_EXIT && FLAG_PARIDAD == IMPAR)
        {
            usleep(10);
        }

        pthread_mutex_lock(&lock);
        int par;
        do
        {
            par = aleatorio_intervalo(2, MILLON);
        } while (par % 2 == IMPAR);

        arr[i] = par;
        pthread_mutex_unlock(&lock);
    }

    while (i < ARRAYSIZE)
    {
        if ((i % 2) == PAR)
        {
            pthread_mutex_lock(&lock);
            if (arr[i] < 100000)
            {
                counter = counter + 1;
            }
            printf("%d: %d ", i, arr[i]);
            i = i + 1;
            pthread_mutex_unlock(&lock);
        }
        else
        {
            usleep(10000);
        }
    }
}

void *impares_f(void *parm)
{
    while (FLAG_EXIT)
    {
        while (FLAG_EXIT && FLAG_PARIDAD == PAR)
        {
            usleep(10);
        }

        pthread_mutex_lock(&lock);
        int impar;
        do
        {
            impar = aleatorio_intervalo(1, MILLON);
        } while (impar % 2 == PAR);

        arr[i] = impar;
        pthread_mutex_unlock(&lock);
    }

    while (i < ARRAYSIZE)
    {
        if ((i % 2) == IMPAR)
        {
            pthread_mutex_lock(&lock);
            if (arr[i] < 100000)
            {
                counter = counter + 1;
            }
            printf("%d: %d ", i, arr[i]);
            i = i + 1;
            pthread_mutex_unlock(&lock);
        }
        else
        {
            usleep(10000);
        }
    }
}

unsigned int aleatorio_intervalo(unsigned int min, unsigned int max)
{
    int r;
    const unsigned int rango = 1 + max - min;
    const unsigned int trozos = RAND_MAX / rango;
    const unsigned int limite = trozos * rango;
    do
    {
        r = rand();
    } while (r >= limite);

    return min + (r / trozos);
}