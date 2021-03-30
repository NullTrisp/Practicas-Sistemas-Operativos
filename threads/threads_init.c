#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>

pthread_t ntid;

/**
 * function to print pid and tid of thread
 * @param s thread name
 * @returns void
 */
void print_ids(const char *s)
{
    pid_t pid = getpid();           //process id
    pthread_t tid = pthread_self(); //thread id

    printf("%s pid %u tid %u\n", s, (unsigned int)pid, (unsigned int)tid);

    return;
}

/**
 * function to execute thread
 * @returns void
 */
void *thread_fun(void *args)
{
    print_ids("New thread: ");
    return NULL;
}

int main(int argc, char const *argv[])
{
    int err = pthread_create(&ntid, NULL, &thread_fun, NULL);
    if (err != 0)
    {
        perror("Error creating thread");
    }
    else
    {
        print_ids("Main thread: ");
        pthread_join(ntid, NULL); //main thread must remain alive
        // usleep(100); //main thread must remain alive
        return 0;
    }
}
