#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

int main(int argc, char const *argv[])
{
    pid_t sonA = fork();

    if (sonA > 0)
    {
        printf("Im the father PID %d\n", getpid());
        exit(0);
    }
    else if (sonA == 0)
    {
        sleep(1);
        printf("Im the son PID %d and my father is PID %d\n", getpid(), getppid());
        exit(0);
    }

    return 0;
}
