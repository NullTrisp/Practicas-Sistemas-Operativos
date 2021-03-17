#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>
#include <sys/types.h>
#define SIZE 4096

int main(int argc, char const *argv[])
{
    pid_t son;
    int pipeline[2];
    char buffer[SIZE];

    if (pipe(pipeline) < 0) //error case
    {
        perror("Error creating pipe");
        return -1;
    }

    if ((son = fork()) < 0) //error case
    {
        perror("Error new process");
        return -1;
    }
    else if (son > 0) //father reads
    {
        close(pipeline[1]);
        read(pipeline[0], buffer, SIZE);
        printf("Son has sent this message: \n %s\n", buffer);
        wait(NULL);
        close(pipeline[0]);
    }
    else //son writes
    {
        close(pipeline[0]);
        dup2(pipeline[1], STDOUT_FILENO); //everything printed goes to pipeline
        execl("./slave", "slave", NULL);
    }

    puts("End of file");

    return 0;
}
