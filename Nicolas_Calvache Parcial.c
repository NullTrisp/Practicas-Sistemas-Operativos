#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

//hilos a crear
pthread_t master_t, escribe_t, primo_t, fibonnaci_t;

//flags para sincronizar hilos
int EXIT_FLAG = -1, CHANGE_FLAG = 0, FACTORIAL_FLAG = 0, FIBONACCI_FLAG = 0, PRIME_FLAG = 0, positive_value;
//valor del factorial
long unsigned int factorial_value;

//funciones de hilos
void *master_f();
void *escribe_f();
void *primo_f();
void *fibonnaci_f();

//funciones extra
long unsigned int factorial();
long unsigned int factorial_p();
void is_prime();
void fibonacci_find();

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
        //mientras se haya cambiado el valor se espera, ademas de esperar a que fibonacci y primo hayan terminado
        while (CHANGE_FLAG == 1 || FACTORIAL_FLAG == 1)
        {
            usleep(10);
        }

        //restablezco flags de fibonacci y primo
        FIBONACCI_FLAG = 0;
        PRIME_FLAG = 0;
        printf("\n\n\nI'm the master thread: %d\n", master_t);
        puts("Insert a positive value:");
        scanf("%d", &positive_value);
        //se recibe valor por lo tanto levanto la flag de cambio de valor
        CHANGE_FLAG = 1;
    } while (positive_value != -1);
    //flag para cancelar todos los while de los hilos
    EXIT_FLAG = 0;
}

void *escribe_f()
{
    //flag general de programa
    while (EXIT_FLAG < 0)
    {
        //pongo al hilo a dormir hasta que haya un ingreso de dato
        while (EXIT_FLAG < 0 && CHANGE_FLAG == 0)
        {
            usleep(10);
        }
        if (EXIT_FLAG < 0)
        {
            //realiza factorial
            factorial_value = factorial(positive_value);
            printf("factorial: %lu\n", factorial_value);
            //levanto la flag de factorial terminado y cambio de valor baja
            FACTORIAL_FLAG = 1;
            CHANGE_FLAG = 0;
        }
    }
}

long unsigned int factorial(long unsigned int n)
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

long unsigned int factorial_p(long unsigned int n, long unsigned int acum)
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

void *primo_f()
{
    //flag general de programa
    while (EXIT_FLAG < 0)
    {
        //pongo al hilo a dormir hasta que haya terminado el factorial
        while (EXIT_FLAG < 0 && FACTORIAL_FLAG == 0)
        {
            usleep(10);
        }
        if (EXIT_FLAG < 0)
        {
            //realizo el primo
            is_prime(factorial_value - 1);
            //el hilo levanta flag de que ha terminado
            PRIME_FLAG = 1;
            //espera a que fibonacci termine
            while (FIBONACCI_FLAG == 0 && FACTORIAL_FLAG == 1)
            {
                usleep(10);
            }
            //levanta flag de que ha terminado la fase B
            FACTORIAL_FLAG = 0;
        }
    }
}

void is_prime(long unsigned int num)
{
    int flag = 1;
    for (int i = 2; i < num; i++)
    {
        if (num % i == 0)
        {
            flag = 0;
            break;
        }
    }
    if (flag == 1)
        printf("%lu is prime number\n", num);
    else
        printf("%lu is not a prime number\n", num);
    return 0;
}

void *fibonnaci_f()
{
    //flag general de programa
    while (EXIT_FLAG < 0)
    {
        //pongo al hilo a dormir hasta que haya terminado el factorial
        while (EXIT_FLAG < 0 && FACTORIAL_FLAG == 0)
        {
            usleep(10);
        }
        if (EXIT_FLAG < 0)
        {
            //realizo fibonacci
            fibonacci(factorial_value - 1);
            //el hilo levanta flag de que ha terminado
            FIBONACCI_FLAG = 1;
            //espeara a que primo haya terminado
            while (PRIME_FLAG == 0 && FACTORIAL_FLAG == 1)
            {
                usleep(10);
            }
            //levanta flag de que ha terminado la fase B
            FACTORIAL_FLAG = 0;
        }
    }
}

void fibonacci(long long unsigned int n)
{
    unsigned long long int i, t1 = 0, t2 = 1, siguiente;
    int flag = 0;
    for (i = 1; i <= n; ++i)
    {
        if (t1 == n || t2 == n)
        {
            flag = 1;
            i = n + 1;
        }

        siguiente = t1 + t2;
        t1 = t2;
        t2 = siguiente;
    }

    if (flag == 1 || n == 0)
    {
        printf("%lu is in the fibonacci sequence!\n", n);
    }
    else
    {
        printf("%lu is not in the fibonacci sequence!\n", n);
    }

    return;
}
