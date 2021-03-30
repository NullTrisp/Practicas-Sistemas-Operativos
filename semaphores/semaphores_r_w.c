#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <fcntl.h>

#define SEMAPHORE_NAME "/semaphore"

sem_t *semaphore;
static int *shared_var;

int main(int argc, char const *argv[])
{
    shared_var = mmap(NULL, sizeof *shared_var, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    semaphore = sem_open(SEMAPHORE_NAME, O_CREAT, S_IRUSR | S_IWUSR, 1);

    if (fork() > 0)
    {
        if (fork() == 0)
        {
            usleep(1);
            sem_wait(semaphore);
            printf("Value is: %d\n", *shared_var);
            sem_post(semaphore);
            exit(0);
        }
        else
        {
            while (wait(NULL) > 0)
                ;
            munmap(shared_var, sizeof *shared_var);
            sem_close(semaphore);
            sem_unlink(SEMAPHORE_NAME);
            return 0;
        }
    }
    else
    {
        sem_wait(semaphore);
        printf("Input value: ");
        scanf("%d", *&shared_var);
        sem_post(semaphore);
        exit(0);
    }
}
