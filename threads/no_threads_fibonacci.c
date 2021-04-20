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
void print_prime();

int main(int argc, char const *argv[])
{
    print_prime();
    printf("fibonacci to %lu is %lu\n", nth, fibonacci(0, 1, nth));

    return 0;
}

long unsigned int fibonacci(long unsigned int prev, long unsigned int current, long unsigned int nth)
{
    return (nth == 0) ? 0 : (nth == 1) ? current
                                       : fibonacci(current, current + prev, nth - 1);
}

void print_prime()
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
}