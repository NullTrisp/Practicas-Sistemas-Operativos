#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

int main(int argc, char
    const * argv[]) {
    int exit = 0;

    char option;

    while (exit == 0) {
    printf("Select an option\n[w] ---> ls command\n[a] ---> ps command\n[s] ---> exit\n");
    scanf("%c", &option);
        
        if (fork() > 0) {
            wait(NULL);
            if(option == 's') {
                _exit(0);
            }
        } else {
            if (option == 'w') {
                execlp("/bin/ls", "ls", NULL);
            } else if (option == 'a') {
                execlp("/bin/ps", "ps", NULL);
            } else if(option == 's') {
                _exit(0);
            } else {
                _exit(0);
            }
        }
    }

    return 0;
}
