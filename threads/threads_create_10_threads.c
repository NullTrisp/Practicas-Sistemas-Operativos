#include <pthread.h>
#include <unistd.h>

#define LIMIT 5

pthread_t threads[LIMIT];
int aux;
int index = 0;

void *print_created(void *args);

int main(int argc, char const *argv[])
{
    for (int i = 0; i < LIMIT; i++)
    {
        pthread_create(&threads[i], NULL, &print_created, i);
        usleep(100);
    }

    pthread_join(threads[LIMIT - 1], NULL);

    return 0;
}

void *print_created(void *args)
{
    int index = (int *)args;
    printf("He nacido. Soy el hilo %d con ID %u\n", index + 1, (unsigned int)pthread_self());
    usleep(1000);
    pthread_join(threads[(LIMIT - 1) - index], NULL);
    printf("El hilo %d con ID %u finaliza\n", index + 1, (unsigned int)pthread_self());
}
