#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/mman.h>

static int *a;
static int *b;
static int *c;

int main(int argc, char const *argv[])
{
    pid_t son;
    a = mmap(NULL, sizeof *a, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    b = mmap(NULL, sizeof *a, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    c = mmap(NULL, sizeof *a, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    *a = 0;
    *b = 0;
    *c = 0;
    son = fork();

    if (son > 0)
    {
        printf("First value:\n ");
        scanf("%d", *&a);
        printf("Second value value:\n ");
        scanf("%d", *&b);
        wait(NULL);
        printf("%d\n", *c);
    }
    else
    {
        while (*a == 0 || *b == 0)
        {
            sleep(0.1);
        }

        *c = *a + *b;
        exit(0);
    }

    return 0;
}
