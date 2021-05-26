#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/syscall.h>
#include <sys/types.h>

void *fun_t1();
void *fun_t2();
void handler(int arg);

pthread_t t1, t2;
pid_t process;
pthread_mutex_t lock;

int main(int argc, char const *argv[])
{
    signal(SIGURG, handler);

    pthread_mutex_init(&lock, NULL);
    pthread_create(&t1, NULL, &fun_t1, NULL);
    pthread_create(&t2, NULL, &fun_t2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_mutex_destroy(&lock);
    return 0;
}

void *fun_t1()
{
    while (1)
    {
        sleep(5);
        puts("let's stop t2");
        pthread_mutex_lock(&lock);
        kill(process, SIGURG);
        sleep(5);
        puts("let's start t2");
        pthread_mutex_unlock(&lock);
    }
    return 0;
}
void *fun_t2()
{
    printf("TID is %d\n", (process = syscall(__NR_gettid)));
    while (1)
    {
        puts("I'm t2 and now I'm working");
        sleep(2);
    }

    return 0;
}

void handler(int arg)
{
    puts("Handler init");
    pthread_mutex_lock(&lock);
    pthread_mutex_unlock(&lock);
}