#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

int main()
{
    pid_t son = fork();
    int a, b;

    if (son > 0)
    {
        printf("From father: I'm the father [%d] and I wait\n\n", getpid());
        wait(son);
    }
    else if (son == 0)
    {
        printf("From son: I'm the son [%d] and sum values\n", getpid());
        printf("From son: My father is %d\n", getppid());
        puts("From son: Enter first value:");
        scanf("%d", &a);
        puts("From son: Enter second value:");
        scanf("%d", &b);
        printf("From son: the sum is: %d\n\n", a + b);
        _exit(0);   //better way to end a process
    }
    else
    {
        perror("Shitty ass failure ");
    }

    puts("From father: Bye bye");

    return 0;
}
