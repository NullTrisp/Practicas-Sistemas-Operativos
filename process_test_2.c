#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

int main()
{
    char aux;
    aux = getchar();
    pid_t sonA = fork(), sonB = fork();

    if (sonA > 0 && sonB > 0) //father
    {
        puts("Father");
        printf("%d %d %d\n", getpid(), sonA, sonB);
        while (wait(NULL) > 0)
            ;
    }
    else if (sonA == 0 && sonB > 0) //sonA
    {
        puts("sonA");
        printf("%d %d %d\n", getpid(), sonA, sonB);
        //printf("A %c\n", aux);
        _exit(0);
    }
    else if (sonB == 0 && sonA > 0) //sonB
    {
        puts("sonB");
        printf("%d %d %d\n", getpid(), sonA, sonB);
        //printf("B %c\n", aux);
        _exit(0);
    }
    else
    {
        perror("Shitty ass failure ");
    }

    return 0;
}
