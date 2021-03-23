#include <stdio.h>
#include <unistd.h>
#include <sys/types.h> //tipos de datos de linux kernel
#include <wait.h>

int main()
{
    //process id datatype
    pid_t son = fork(); //proceso hijo  //padre > 0   //copia hijo = 0
    int n = 5;
    if (son > 0) //proceso padre
    {
        puts("I'm the father and I wait");
        wait(NULL); //waits for the child process to die one son
        //while (wait(NULL) > 0) //waits for the child process to die all sons
    }
    else if (son == 0)
    {
        puts("I'm the son and now me voy a tomar por culo");
        ++n; //n variable copy
        printf("n copy %d\n", n);
        return 0;
    }
    else
    {
        perror("Shitty ass failure ");
    }

    printf("The son is now dead and the variable is %d \n", n);

    return 0;
}
