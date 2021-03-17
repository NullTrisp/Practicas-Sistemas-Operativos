#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <stdlib.h>
#include <sys/mman.h>

static int *shared_var;

int main(int argc, char const *argv[])
{
    pid_t son;
    shared_var = mmap(NULL, sizeof *shared_var, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    *shared_var = 0;
    son = fork();

    if (son > 0)
    {
        puts("Father process waiting for son to die");
        wait(NULL);
        printf("Son has died shared variable is %d\n", *shared_var);
    }
    else
    {
        puts("Son waiting to change shared variable");
        scanf("%d", *&shared_var);
        exit(0);
    }

    return 0;
}
