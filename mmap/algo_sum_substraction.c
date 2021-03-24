#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <stdlib.h>
#include <sys/mman.h>

static int *shared_var;

int main(int argc, char const *argv[])
{
    const int LIMIT = 100;
    shared_var = mmap(NULL, sizeof *shared_var, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    *shared_var = 0;

    pid_t sum, subtraction;

    sum = fork();
    if (sum > 0) //father
    {
        subtraction = fork();
        if (subtraction == 0) //substraction
        {
            for (int i = 0; i < LIMIT; i++)
            {
                *shared_var = *shared_var - 1;
                printf("substraction: %d\n", *shared_var);
            }
            exit(0);
        }
        else //father
        {
            while (wait(NULL) > 0)
                ;
            printf("\nFinal result: %d\n", *shared_var);
            munmap(shared_var, sizeof *shared_var); //destroys shared var
            exit(0);
        }
    }
    else //sum
    {
        for (int i = 0; i < LIMIT; i++)
        {
            *shared_var = *shared_var + 1;
            printf("sum: %d\n", *shared_var);
        }
        exit(0);
    }

    return 0;
}
