#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <stdlib.h>
#include <sys/mman.h>

static int *shared_var;
int array_size;

int main(int argc, char const *argv[])
{
    array_size = 2;
    /* sizeof(int) * array_size  = new array*/
    shared_var = mmap(NULL, sizeof(int) * array_size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    if (fork() > 0)
    {
        wait(NULL);
        printf("The array values are: %d, %d.\n", shared_var[0], shared_var[1]);
    }
    else
    {
        shared_var[0] = 420;
        shared_var[1] = 69;
        exit(0);
    }

    return 0;
}
