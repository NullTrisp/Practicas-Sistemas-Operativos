#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

int main(int argc, char const *argv[])
{
    puts("oli");
    execlp("//home/trisp/Documents/Practicas-Sistemas-Operativos", "./test", NULL);

    return 0;
}