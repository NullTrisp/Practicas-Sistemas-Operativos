#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>
#include <sys/types.h>

int main(int argc, char const *argv[])
{
    int pipelineA[2], pipelineB[2], a, b, c; //0 reads, 1 writes

    pid_t son;

    if (pipe(pipelineA) < 0 || pipe(pipelineB) < 0)
    {
        perror("Error creating pipe");
        return -1;
    }

    if ((son = fork()) < 0)
    {
        perror("Error creating pipe");
    }
    else if (son > 0)
    {
        close(pipelineA[0]);
        close(pipelineB[1]);
        printf("\nInsert first value: ");
        scanf("%d", &a);
        while (a != -1)
        {
            printf("\nInsert second value: ");
            scanf("%d", &b);
            write(pipelineA[1], &a, sizeof(a));
            write(pipelineA[1], &b, sizeof(b));
            read(pipelineB[0], &c, sizeof(c));

            printf("\nSum is: %d\n", c);
            printf("\nInsert first value: ");
            scanf("%d", &a);
        }

        kill(son, SIGKILL);
    }
    if (son == 0)
    {

        close(pipelineA[1]);
        close(pipelineB[0]);

        while (1)
        {
            read(pipelineA[0], &a, sizeof(a));
            read(pipelineA[0], &b, sizeof(b));

            c = a + b;
            write(pipelineB[1], &c, sizeof(c));
        }
    }

    return 0;
}
