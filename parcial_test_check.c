
/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <pthread.h>
#include<time.h>
#include <stdlib.h>


#define MILLON 1000000
#define LIMIT 1000

pthread_t master_t, pares_t, impares_t;
pthread_mutex_t lock;

void *master_f();
void *pares_f();
void *impares_f();
unsigned int aleatorio_intervalo(unsigned int min, unsigned int max);

int arr[LIMIT], i = 0, FLAG_EXIT = -1, FLAG_MAIN = 1, FLAG_PAR = 0, FLAG_IMPAR = 0, counter = 0;


int main()
{
    srand(time(NULL));
    pthread_mutex_init(&lock, NULL);
    pthread_create(&master_t, NULL, &master_f, NULL);
    pthread_create(&pares_t, NULL, &pares_f, NULL);
    pthread_create(&impares_t, NULL, &impares_f, NULL);
    
    pthread_join(master_t, NULL);
    pthread_join(pares_t, NULL);
    pthread_join(impares_t, NULL);

    pthread_mutex_destroy(&lock);
    
    return 0;
}

void *master_f()
{
    while(i < LIMIT)
    {
        if((i % 2) == 0 || i == 0)
        {
            FLAG_MAIN = 0;
            FLAG_PAR = 1;
            FLAG_IMPAR = 0;
        }
        else
        {
            FLAG_MAIN = 0;
            FLAG_PAR = 0;
            FLAG_IMPAR = 1;
        }
        
        while(FLAG_MAIN == 0)
        {
            usleep(10);
        }
        
        i = i + 1;
    }
    
    FLAG_EXIT = 0;
    FLAG_IMPAR = 1;
    FLAG_PAR = 1;
    //sleep(1);
    
    while(FLAG_IMPAR == 1 || FLAG_PAR == 1)
    {
        usleep(100);
    }
    
    printf("\ncounter: %d\n", counter);
    
    return NULL;
}

void *pares_f()
{
    while(FLAG_EXIT < 0)
    {
        while(FLAG_EXIT < 0 && (FLAG_MAIN == 1 || FLAG_IMPAR == 1))
        {
            usleep(10);
        }
        int par;
        do
        {
            par = aleatorio_intervalo(2, MILLON);
        } while((par % 2) == 1);
        arr[i] = par;
        FLAG_PAR = 0;
        FLAG_MAIN = 1;
    }
    
    for (int j = 0; j < LIMIT; j++) {
        if((j % 2) == 0 || j == 0)
        {
            if(arr[j] < 100000)
            {
                pthread_mutex_lock(&lock);
                counter = counter + 1;
                pthread_mutex_unlock(&lock);
            }
            printf("i: %d par: %d\n", j, arr[j]);
        }
    }
    
    FLAG_PAR = 0;
    while(FLAG_IMPAR == 1)
    {
        usleep(10);
    }
    
    return NULL;
}

void *impares_f()
{
    while(FLAG_EXIT < 0)
    {
        while(FLAG_EXIT < 0 && (FLAG_MAIN == 1 || FLAG_PAR == 1))
        {
            usleep(10);
        }
        int impar;
        do
        {
            impar = aleatorio_intervalo(1, MILLON);
        } while((impar % 2) == 0);
        arr[i] = impar;
        FLAG_IMPAR = 0;
        FLAG_MAIN = 1;
    }

    
    for (int k = 0; k < LIMIT; k++) {
        if((k % 2) == 1)
        {
            if(arr[k] < 100000)
            {
                pthread_mutex_lock(&lock);
                counter = counter + 1;
                pthread_mutex_unlock(&lock);
            }
            printf("i: %d impar: %d\n", k, arr[k]);
        }
    }
    
    FLAG_IMPAR = 0;
    while(FLAG_PAR == 1)
    {
        usleep(10);
    }
    
    return NULL;
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

