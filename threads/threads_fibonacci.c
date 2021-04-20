#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <time.h>

#define TRUE 1
#define FALSE 0

long unsigned int const n = 2342352433LU;
long unsigned int const nth = 100000LU;

long unsigned int fibonacci(long unsigned int prev, long unsigned int current, long unsigned int nth);
void *print_prime();
void *print_fibonacci();

pthread_t ntid_fibonacci, ntid_prime;

int main(int argc, char const *argv[])
{
    pthread_create(&ntid_fibonacci, NULL, &print_fibonacci, NULL);
    pthread_create(&ntid_prime, NULL, &print_prime, NULL);

    pthread_join(ntid_fibonacci, NULL);
    pthread_join(ntid_prime, NULL);

    return 0;
}

void *print_fibonacci()
{
    printf("fibonacci to %lu is %lu\n", nth, fibonacci(0, 1, nth));
    return NULL;
}

void *print_prime()
{
    int is_prime = TRUE;

    if (n == 1)
    {
        puts("Value is 1");
    }
    else
    {
        for (int i = 2; i < n; i++)
        {
            if (n % i == 0)
            {

                is_prime = FALSE;
                // break;
            }
        }
        if (is_prime)
        {
            printf("Value %lu is prime\n", n);
        }
        else
        {
            printf("Value %lu is not prime\n", n);
        }
    }

    return NULL;
}

long unsigned int fibonacci(long unsigned int prev, long unsigned int current, long unsigned int nth)
{
    return (nth == 0) ? 0 : (nth == 1) ? current
                                       : fibonacci(current, current + prev, nth - 1);
}