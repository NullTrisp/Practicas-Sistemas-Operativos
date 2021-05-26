#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>

void handler(int sigum);

void divide();
void create_son();

pid_t pid;

int main(int argc, char const *argv[])
{
    while (1)
    {
        if (fork() > 0)
        {
            pid = getpid();
            signal(SIGINT, handler);
            wait(NULL);
        }
        else
        {
            while (1)
            {
                signal(SIGFPE, handler);
                int a, b, c;
                printf("First value: ");
                scanf("%d", &a);
                printf("Second value: ");
                scanf("%d", &b);
                c = a / b;
                printf("res is: %d\n", c);
            }
        }
    }

    return 0;
}

void handler(int sigum)
{
    if (sigum == SIGFPE && pid != getpid())
    {
        puts("Just why?..\n");
        exit(0);
    }
    else if (sigum == SIGINT && pid == getpid())
    {
        puts("oli");
        exit(0);
    }
}