#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 3
//handlers
void master_handler_f(int signum);
void par_handler_f(int signum);
void impar_handler_f(int signum);

//threads
void *master_f(void *args);
void *par_f(void *args);
void *impar_f(void *args);

pthread_t master_t, par_t, impar_t;

int matrix[SIZE][SIZE];
int current_index, i, j;
int main(int argc, char const *argv[])
{
    pthread_create(&master_t, NULL, &master_f, NULL);
    pthread_create(&par_t, NULL, &par_f, NULL);
    pthread_create(&impar_t, NULL, &impar_f, NULL);

    pthread_join(master_t, NULL);
    pthread_join(par_t, NULL);
    pthread_join(impar_t, NULL);
    return 0;
}

void *master_f(void *args)
{
    signal(SIGUSR1, master_handler_f);
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            current_index = i + j;
            if (current_index == 0) //par
            {
                pthread_kill(par_t, SIGUSR1);
            }
            else if ((current_index % 2) == 0) //par
            {
                pthread_kill(par_t, SIGUSR1);
            }
            else //impar
            {
                pthread_kill(impar_t, SIGUSR1);
            }
            pause();
        }
    }

    puts("\n");
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        puts("");
    }
    puts("\n");

    pthread_kill(impar_t, SIGURG);
    return 0;
}

void *par_f(void *args)
{
    signal(SIGUSR2, par_handler_f);
    signal(SIGUSR1, par_handler_f);
    while (1)
    {
        pause();
        puts("par thread: input value");
        scanf("%d", &matrix[i][j]);
        pthread_kill(master_t, SIGUSR1);
    }
}

void *impar_f(void *args)
{
    signal(SIGURG, impar_handler_f);
    signal(SIGUSR1, impar_handler_f);
    while (1)
    {
        pause();
        puts("impar thread: input value");
        scanf("%d", &matrix[i][j]);
        pthread_kill(master_t, SIGUSR1);
    }
}

void par_handler_f(int signum)
{
    if (signum == SIGUSR2)
    {
        puts("par thread ready to die!");
        pthread_exit(0);
    }
}

void impar_handler_f(int signum)
{
    if (signum == SIGURG)
    {
        puts("impar thread ready to die!");
        pthread_kill(par_t, SIGUSR2);
        pthread_exit(0);
    }
}

void master_handler_f(int signum)
{
}
