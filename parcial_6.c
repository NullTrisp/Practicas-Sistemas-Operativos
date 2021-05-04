#include <pthread.h>
#include <stdio.h>

pthread_t master_t, escribe_t, primo_t, fibonnaci_t;

int EXIT_FLAG = -1, CHANGE_FLAG = 0, positive_value;

void *master_f();
void *escribe_f();
void *primo_f();
void *fibonnaci_f();

int factorial();
int factorial_p();

int main(int argc, char const *argv[])
{
    pthread_create(&master_t, NULL, &master_f, NULL);
    pthread_create(&escribe_t, NULL, &escribe_f, NULL);
    pthread_create(&primo_t, NULL, &primo_f, NULL);
    pthread_create(&fibonnaci_t, NULL, &fibonnaci_f, NULL);

    pthread_join(master_t, NULL);
    pthread_join(escribe_t, NULL);
    pthread_join(primo_t, NULL);
    pthread_join(fibonnaci_t, NULL);

    return 0;
}

void *master_f()
{
    do
    {
        printf("Soy hilo master: %d\n", master_t);
        scanf("%d", &positive_value);
        CHANGE_FLAG = 1;
    } while (positive_value != -1);
    EXIT_FLAG = 0;
}

void *escribe_f()
{
    while (EXIT_FLAG < 0)
    {
        while (EXIT_FLAG < 0 && CHANGE_FLAG == 0)
        {
            usleep(10);
        }
        if (EXIT_FLAG < 0)
        {
            printf("%lu\n", factorial(positive_value));
            puts("value recieved");
            CHANGE_FLAG = 0;
        }
    }
}

int factorial(int n)
{
    if (n == 0)
    {
        return 1;
    }
    else
    {
        return factorial_p(n, n);
    }
}

int factorial_p(int n, int acum)
{
    if (n == 1)
    {
        return acum;
    }
    else
    {
        return factorial_p(n - 1, acum * (n - 1));
    }
}

void *primo_f() {}
void *fibonnaci_f() {}
