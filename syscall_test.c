#include <linux/kernel.h>
#include <stdio.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define __NR_identity 440

int main(int argc, char const *argv[])
{
    if (syscall(__NR_identity) < 0)
    {
        perror("Well shit :/\n");
    }
    else
    {
        printf("Yup you did it :D\n");
    }
    return 0;
}
