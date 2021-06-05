/*
Crear dos hijos apartir del proceso padre, el primer hijo lee un valor
(todo el proceso espera hasta que se lea este numero). el segundo hijo deberá
crear 2 hilos, un proceso itera hasta el valor leido sumando de uno en uno en una variable global
mientras el otro itera restando de uno en uno. finalmente el proceso padre muestra por
pantalla el valor final de esta variable
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <sys/types.h>
#include <pthread.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/mman.h>

pid_t son_1_p, son_2_p;

pthread_t son_2_sum_t, son_2_sub_t;

void *son_2_sum_f();
void *son_2_sub_f();

static int *shared_var, *value;

void wait_handler(int signum);

int main(int argc, char const *argv[])
{
    shared_var = mmap(NULL, sizeof *shared_var, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    *shared_var = 0;
    value = mmap(NULL, sizeof *value, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    *value = 0;
    if ((son_1_p = fork()) > 0)
    {
        signal(SIGUSR1, wait_handler);
        pause();
        puts("father");
        if ((son_2_p = fork()) == 0)
        {
            pthread_create(&son_2_sub_t, NULL, &son_2_sub_f, NULL);
            pthread_create(&son_2_sum_t, NULL, &son_2_sum_f, NULL);

            pthread_join(son_2_sum_t, NULL);
            pthread_join(son_2_sub_t, NULL);

            kill(getppid(), SIGUSR1);
        }
        pause();
        printf("value is: %d", *value);
    }
    else
    {
        puts("input value");
        scanf("%d", &*shared_var);
        kill(getppid(), SIGUSR1);
    }

    return 0;
}

void wait_handler(int signum)
{
}

void *son_2_sum_f()
{
    for (int i = 0; i < *shared_var; i++)
    {
        puts("sum");
        *value = *value + 1;
        pthread_kill(son_2_sub_t, SIGUSR1);
        pause();
    }
}

void *son_2_sub_f()
{
    for (int i = 0; i < *shared_var; i++)
    {
        pause();
        puts("sub");
        *value = *value - 1;
        pthread_kill(son_2_sum_t, SIGUSR1);
    }
}