#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void father_handler(int signum);
void son_handler(int signum);

int main(int argc, char const *argv[])
{
    pid_t son;
    if ((son = fork()) > 0)
    {
        signal(SIGUSR1, father_handler);
        sleep(2);
        puts("I'm father I'll send a signal to child");
        kill(son, SIGUSR1);
        puts("... I'll wait for child's signal");
        pause();    //pause until a signal recieved

        exit(0);
    }
    else
    {
        signal(SIGUSR1, son_handler);
        puts("I'm the son and I'll wait father signal");
        pause();

        exit(0);
    }
}

void father_handler(int signum)
{
    puts("I'm the father: I've recieved a signal from child");
}

void son_handler(int signum)
{
    puts("I'm the son: I've recieved a signal from father");
    sleep(2);
    kill(getppid(), SIGUSR1); //send signals between process
}