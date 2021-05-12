#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>
#include <signal.h>

void *leer_numero();
void *escribir_numero();
unsigned long long int factorial(int);
void leer_handler(int signum);
void escribir_handler(int signum);

int seguir_leyendo = 1;
int dato;
pthread_t lee, escribe;

int main()
{

    pthread_create(&lee, NULL, &leer_numero, NULL);
    pthread_create(&escribe, NULL, &escribir_numero, NULL);
    pthread_join(lee, NULL);
    pthread_join(escribe, NULL);

    return 0;
}

void *leer_numero(int signum)
{
    signal(SIGUSR1, leer_handler);

    while (seguir_leyendo == 1)
    {
        printf("\nSoy el hilo %u. Introduce un número:", (unsigned int)pthread_self());
        scanf("%d", &dato);
        if (dato != -1)
        {
            pthread_kill(escribe, SIGUSR1);
            pause();
        }
        else
        {
            seguir_leyendo = 0;
            pthread_kill(escribe, SIGUSR1);
            break;
        }
    }
    return 0;
}
void *escribir_numero()
{
    signal(SIGUSR1, escribir_handler);
    while (seguir_leyendo == 1)
    {
        pause();
        if (seguir_leyendo == 0)
            break;
        printf("Soy el hilo %u y el factorial de %d es %llu\n", (unsigned int)pthread_self(), dato, factorial(dato));
        pthread_kill(lee, SIGUSR1);
    }
    return 0;
}
unsigned long long int factorial(int num)
{
    int i;
    unsigned long long int fact;
    for (i = 1, fact = 1; i <= num; i++)
    {
        fact = fact * i;
    }
    return fact;
}

void leer_handler(int signum) {}
void escribir_handler(int signum) {}