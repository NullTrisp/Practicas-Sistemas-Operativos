#include <stdio.h>

int main()
{

    int value, pos, i, arrSize;

    printf("Insert array size: \n");
    scanf("%d", &arrSize);

    int arr[arrSize];

    for (i = 0; i < arrSize; ++i)
    {
        printf("Value to insert to array in position %d!\n", 1 + i);
        scanf("%d", &arr[i]);
    }

    printf("\nYour array is: \n");
    for (i = 0; i < arrSize; ++i)
    {
        printf("%d ", arr[i]);
    }

    printf("\n\nInsert position to insert new value!\n");
    scanf("%d", &pos);

    if (pos > arrSize || pos < 0)
    {
        printf("Position value is not valid!\n");
        return 1;
    }

    printf("Insert new value!\n");
    scanf("%d", &value);

    for(i=arrSize; i>=pos; i--)
        {
            arr[i] = arr[i-1];
        }
        
        arr[pos-1] = value;

    printf("\nYour new array is: \n");
    for (i = 0; i < arrSize + 1; ++i)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
