#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>
#include <sys/types.h>

int main(int argc, char const *argv[])
{
    printf("I'm the father with PID %d and my father is %d\n", getpid(), getppid());

    pid_t sonA = fork();

    if (sonA == 0) //sonA process
    {
        sleep(200);
        printf("I'm the son with PID %d and my father is %d\n", getpid(), getppid());
        exit(0);
    }
    else if (sonA > 0) //parent process
    {
        printf("I'm the father I'll wait and my son is %d\n", (int)sonA);
        while (wait(NULL))
            ;
    }

    return 0;
}
