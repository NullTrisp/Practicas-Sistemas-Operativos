#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

void handler(int sigum);

int main(int argc, char const *argv[])
{
    signal(SIGINT, handler);
    signal(SIGQUIT, handler);
    while (1)
    {
        puts("gamba");
        sleep(2);
    }
    return 0;
}

void handler(int sigum)
{
    if (sigum == SIGINT)
    {
        puts("\nCtrl + c");
        exit(0);
    }
    else if (sigum == SIGQUIT)
    {
        puts("\nCtrl + d");
        exit(0);
    }
    else
    {
        puts("\nidunnu");
        exit(0);
    }
}
