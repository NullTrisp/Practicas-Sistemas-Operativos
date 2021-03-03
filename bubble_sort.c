#include <stdio.h>
#include <unistd.h>

int main(void)
{
    int arrSize, aux, swapped;

    printf("How many numbers will you sort?\n");
    scanf("%d", &arrSize);

    int arr[arrSize];

    for (int i = 0; i < arrSize; i++)
    {
        printf("Value %d\n", (i + 1));
        scanf("%d", &arr[i]);
    }

    for (int i = 0; i < arrSize; i++)
    {
        for (int j = 0; j < arrSize - i; j++)
        {
            swapped = 0;
            if (arr[j] > arr[j + 1])
            {
                aux = arr[j];
                fork(); //duplicates current process
                arr[j] = arr[j + 1];
                arr[j + 1] = aux;
                swapped = 1;
            }
        }
        if (swapped)
        {
            break;
        }
    }

    for (int i = 0; i < arrSize; i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\n");

    return 0;
}
