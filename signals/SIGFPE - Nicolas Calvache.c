#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>

void handler(int sigum);

void divide();
void create_son();

int main(int argc, char const *argv[])
{
    if (fork() > 0)
    {
        wait(NULL);
        create_son();
    }
    else
    {
        divide();
    }

    return 0;
}

void divide()
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

void create_son()
{
    if (fork() > 0)
    {
        wait(NULL);
        create_son();
    }
    else
    {
        while (1)
        {
            divide();
        }
    }
}

void handler(int sigum)
{
    puts("Just why?..\n");
    exit(0);
}