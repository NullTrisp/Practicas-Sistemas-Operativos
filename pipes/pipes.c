#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>
#include <sys/types.h>

int main(int argc, char const *argv[])
{
    int pipeline[2]; //0 reads, 1 writes

    pid_t pid;

    if (pipe(pipeline) < 0) //error case
    {
        perror("Error creating pipe");
        return -1;
    }

    if ((pid = fork()) < 0) //error case
    {
        perror("Error new process");
        return -1;
    }
    else if (pid > 0)
    { //father writes case
        close(pipeline[0]);
        char menssage[] = "Hey son, I'm your father";
        write(pipeline[1], menssage, sizeof(menssage));
        wait(NULL);
    }
    else
    { //son reads case
        close(pipeline[1]);
        char buffer[100];
        read(pipeline[0], buffer, sizeof(buffer));
        printf("Hey dad, I've recieved your message: %s\n", buffer);
        exit(0);
    }

    return 0;
}
