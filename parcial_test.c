#include <stdlib.h>

#define MILLON 1000000
#define ARRAYSIZE 6
#define PAR 2
#define IMPAR 1
#define TRUE 1
#define FALSE 0

void *paresFun();
void *imparesFun();
void *masterFun();
unsigned int aleatorio_intervalo();

pthread_t pares, impares, master;
pthread_mutex_t lock;

int arr[ARRAYSIZE], flag, index, exit_flag = FALSE;

int main(int argc, char const *argv[])
{
    srand(time(NULL));

    pthread_mutex_init(&lock, NULL);

    pthread_create(&master, NULL, &masterFun, NULL);
    pthread_create(&pares, NULL, &paresFun, NULL);
    pthread_create(&impares, NULL, &imparesFun, NULL);

    pthread_join(master, NULL);
    pthread_join(pares, NULL);
    pthread_join(impares, NULL);

    for (int i = 0; i < ARRAYSIZE; i++)
    {
        printf("%d: %d ", i, arr[i]);
    }
    printf("\n");

    pthread_mutex_destroy(&lock);

    return 0;
}

void *masterFun()
{
    for (int i = 0; i < ARRAYSIZE; i++)
    {
        index = i;
        if ((i % 2) == 0)
        {
            flag = PAR;
        }
        else
        {
            flag = IMPAR;
        }
        usleep(10000);
    }
    exit_flag = TRUE;
};

void *paresFun()
{
    while (!exit_flag)
    {
        while (flag != PAR && !exit_flag)
        {
            usleep(1);
        }
        pthread_mutex_lock(&lock);
        int par = aleatorio_intervalo(2, MILLON);
        while ((par % 2) != 0)
        {
            par = aleatorio_intervalo(2, MILLON);
        }
        arr[index] = par;
        pthread_mutex_unlock(&lock);
    }
};

void *imparesFun()
{
    while (!exit_flag)
    {
        while (flag != IMPAR && !exit_flag)
        {
            usleep(1);
        }
        pthread_mutex_lock(&lock);
        int impar = aleatorio_intervalo(1, MILLON);
        while ((impar % 2) != 1)
        {
            impar = aleatorio_intervalo(1, MILLON);
        }
        arr[index] = impar;
        pthread_mutex_unlock(&lock);
    }
};

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
