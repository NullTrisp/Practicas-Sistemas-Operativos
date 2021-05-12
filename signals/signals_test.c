#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void handler(int signum);

int main(int argc, char const *argv[])
{
    signal(SIGINT, handler);
    // signal(SIGINT, SIG_IGN); //ignore signal
    signal(SIGUSR1, handler);

    while (1)
    {
        puts("gamba");
        sleep(2);
        raise(SIGUSR1); //send signal
    }
    return 0;
}

void handler(int signum)
{
    switch (signum)
    {
    case SIGINT:
        puts("\na tomar por culo");
        signal(SIGINT, SIG_DFL); //reasign the signal to its primary state
        break;

    case SIGUSR1:
        puts("\nSIGUSR1 dude >_>");

        break;

    default:
        puts("\nno lo sé tu dime");

        break;
    }
}
