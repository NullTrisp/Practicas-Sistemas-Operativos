#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

int main()
{
    int ppid, pid, gid;
    pid = getpid();
    ppid = getppid();
    gid = getpgrp();
    return 0;
}
