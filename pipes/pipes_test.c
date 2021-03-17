//padre crea hijo
//padre lee 2 numeros por teclado despues de haber creado el hijo
//se los pasa al hijo, el los suma y devuelve el resultado al padre
//padre muestra por pantalla
#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>
#include <sys/types.h>

int main(int argc, char const *argv[])
{
    int pipelineA[2], pipelineB[2]; //0 reads, 1 writes

    pid_t pid;

    if (pipe(pipelineA) < 0 || pipe(pipelineB) < 0) //error case in pipes
    {
        perror("Error creating pipe");
        return -1;
    }

    if ((pid = fork()) < 0) //error case in fork
    {
        perror("Error creating new process");
        return -1;
    }
    else if (pid > 0)
    { //father case
        int a, b, c;
        close(pipelineA[0]); //father writes in A
        close(pipelineB[1]); //father reads in B

        printf("First value:\n ");
        scanf("%d", &a);
        printf("Second value value:\n ");
        scanf("%d", &b);

        write(pipelineA[1], &a, sizeof(a)); //send value a to son
        write(pipelineA[1], &b, sizeof(b)); //send value b to son

        wait(NULL); //waits son to die

        read(pipelineB[0], &c, sizeof(c)); //read value c from son

        printf("%d\n", c); //print the value
    }
    else
    { //son case
        int bufferA, bufferB, c;

        close(pipelineA[1]); //son reads in A
        close(pipelineB[0]); //son writes in B

        read(pipelineA[0], &bufferA, sizeof(bufferA)); //read value a from father
        read(pipelineA[0], &bufferB, sizeof(bufferB)); //read value b from father

        c = bufferA + bufferB;              //sum values
        write(pipelineB[1], &c, sizeof(c)); //send value c to father through pipeB
        exit(0);
    }

    return 0;
}
