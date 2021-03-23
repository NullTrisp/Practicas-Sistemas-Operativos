#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>
#include <sys/types.h>

int main(int argc, char const *argv[])
{
    system("ls -l");
    return 0;
}
