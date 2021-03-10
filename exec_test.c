#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

int main(int argc, char const *argv[])
{
    int exit = 0;

    char option;

    while (exit == 0)
    {
        pid_t pid = fork();
        puts("Select an option\n[w] ---> ls command\n[a] ---> ps command\n[s] ---> exit\n");
        scanf("%c", &option);

        switch (option)
        {
        case 'w':
            puts("ls!");
            fork();
            execlp("/bin/ls", "ls", NULL);
            break;
        case 'a':
            puts("ps!");
            break;
        case 's':
            puts("Bye :D!");
            exit = 1;
            break;
        default:
            puts("Select a valid option!\n");
            break;
        }
    }

    return 0;
}