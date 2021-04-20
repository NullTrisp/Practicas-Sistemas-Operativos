#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

#define LIMIT 10

pthread_t threads[LIMIT];
int aux;

void *print_thread(void *args);

int main(int argc, char const *argv[])
{
    for (int i = 0; i < LIMIT; i++)
    {
        pthread_create(&threads[i], NULL, &print_thread, i);
        sleep(1); //Toma tiempo para crear el siguiente hilo(darles orden)
    }

    pthread_join(threads[0], NULL); //espera al primer hilo que es el ultimo en morir

    return 0;
}

void *print_thread(void *args)
{
    int index = (int *)args;
    printf("He nacido. Soy el hilo %d con ID %u\n", index + 1, (unsigned int)pthread_self());
    if (index < LIMIT - 1)
    {
        sleep(2); //espera a que el siguiente hilo sea creado para darle espera
        pthread_join(threads[index + 1], NULL);
    }
    else
    {
        scanf("%d\n", &aux); //el ultimo hilo espera entrada del usuario
    }
    printf("El hilo %d con ID %u finaliza\n", index + 1, (unsigned int)pthread_self());
}
