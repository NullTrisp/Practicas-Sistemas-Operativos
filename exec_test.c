#include <stdio.h>

#include <unistd.h>

#include <sys/types.h>

#include <wait.h>

int main(int argc, char
    const * argv[]) {
    int exit = 0;

    char option;

    puts("Select an option\n[w] ---> ls command\n[a] ---> ps command\n[s] ---> exit\n");
    while (exit == 0) {
        option = getchar();

        if (fork() > 0) {
            if (option == 'w') {
                puts("ls!");
            } else if (option == 'a') {
                puts("ps!");
            } else if (option == 's') {
                exit = 1;
            }
        } else {
            sleep(1);
            if (option == 'w') {
                execlp("/bin/ls", "ls", NULL);
            } else if (option == 'a') {
                execlp("/bin/ps", "ps", NULL);
            } else if (option == 's') {
                exit = 1;
            }
        }
    }

    return 0;
}
