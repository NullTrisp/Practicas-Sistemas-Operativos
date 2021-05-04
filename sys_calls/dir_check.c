#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define SIZE 256

// int main(int argc, char const *argv[])
// {
//     char my_dir[SIZE];

//     if (getcwd(my_dir, SIZE) == NULL)
//     {
//         perror("sucker :P");
//         return -1;
//     }
//     else
//     {
//         printf("%s\n", my_dir);
//     }

//     return 0;
// }

int main(int argc, char const *argv[])
{
    char *aux = malloc(SIZE);

    puts("Insert name and last name: ");
    fgets(aux, SIZE, stdin);

    if ((strlen(aux) > 0) && (aux[strlen(aux) - 1] == '\n'))
    {
        aux[strlen(aux) - 1] = '\0';
    }

    printf("Hi %s nice to meet ya! :D\n", aux);

    return 0;
}
