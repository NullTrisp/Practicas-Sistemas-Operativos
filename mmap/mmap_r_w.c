#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/mman.h>

static int *a;
static int *aux;

int main(int argc, char const *argv[])
{
    pid_t read, write;
    a = mmap(NULL, sizeof *a, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0), aux = mmap(NULL, sizeof *aux, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    *aux = 0, read = fork();

    if (read == 0)
    {
        puts("Input value: \n");
        scanf("%d", *&a);
        *aux = 1;

        while (*aux == 1)
        {
            usleep(20); //miliseconds better performance
        }

        puts("Process read dies!");
        exit(0);
    }
    else
    {
        write = fork();

        if (write == 0)
        {
            while (*aux == 0)
            {
                usleep(20); //miliseconds better performance
            }

            printf("User input: %d\n", *a);
            *aux = 0;
            puts("Process write dies!");
            exit(0);
        }

        wait(NULL);
        puts("I'm the father and i'll die!\n");
        munmap(a, sizeof *a);
        munmap(aux, sizeof *aux);
        exit(0);
    }

    return 0;
}
