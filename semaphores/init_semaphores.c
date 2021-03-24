#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <fcntl.h>
#define SEMAPHORE_NAME "/semaphore"
#define LIMIT 1000000

sem_t *semaphore;
static int *shared_var;

int main(int argc, char const *argv[])
{
    pid_t sum, subtraction;
    shared_var = mmap(NULL, sizeof *shared_var, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    *shared_var = 0;
    semaphore = sem_open(SEMAPHORE_NAME, O_CREAT, S_IRUSR | S_IWUSR, 1); //open semaphore
    sum = fork();

    if (sum > 0) //father
    {
        subtraction = fork();
        if (subtraction == 0) //substraction
        {
            for (int i = 0; i < LIMIT; i++)
            {
                sem_wait(semaphore); //wait
                *shared_var = *shared_var - 1;
                sem_post(semaphore); //continue
            }
            exit(0);
        }
        else //father
        {
            while (wait(NULL) > 0) //wait son to die
                ;
            printf("\nFinal result: %d\n", *shared_var);
            munmap(shared_var, sizeof *shared_var); //destroys shared var
            sem_close(semaphore);                   //close semaphore
            sem_unlink(SEMAPHORE_NAME);             //delete semaphore
            exit(0);
        }
    }
    else //sum
    {
        for (int i = 0; i < LIMIT; i++)
        {
            sem_wait(semaphore); //wait
            *shared_var = *shared_var + 1;
            sem_post(semaphore); //continue
        }
        exit(0);
    }
    return 0;
}
