#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

int main(int argc, char const *argv[])
{
    pid_t pid = fork();

    if (pid > 0)
    {
        wait(NULL);
        puts("My son just killed me by doing an ls command");
    }
    else
    {
        execlp("/bin/ls", "ls", NULL);
        puts("I will never be printed :c");
    }

    return 0;
}
