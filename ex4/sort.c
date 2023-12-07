#include <stdio.h>
int main()
{
    int arr[5], i, j, t;
    for (i = 0; i < 5; i++)
        scanf("%d", &arr[i]);

    for (i = 0; i < 5; i++)
        for (j = 0; j < 5 - i  ; j++)
        {
            if (arr[j] > arr[j +1])
            {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
            
        }

    printf("the array after sorted:\n");
    for (i = 0; i < 5; i++)
        printf("%d\t", arr[i]);
}