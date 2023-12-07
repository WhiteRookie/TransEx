#include <stdio.h>  
  
void bubble_sort(int arr[], int n) {  
    int i, j, temp;  
    for (i = 0; i < n-1; i++) {  
        for (j = 0; j < n-i-1; j++) {  
            if (arr[j] > arr[j+1]) {  
                temp = arr[j];  
                arr[j] = arr[j+1];  
                arr[j+1] = temp;  
            }  
        }  
    }  
}  
  
int main() {  
    int arr[100], n, i;  
    printf("Please enter the number of numbers to sort: ");  
    scanf("%d", &n);  
    for (i = 0; i < n; i++) {
        printf("Input the %dth number: ", i + 1);
        scanf("%d", &arr[i]);  
    }

    bubble_sort(arr, n);  
    printf("Sorted array in ascending order:\n");  
    for (i = 0; i < n; i++) {  
        printf("%d ", arr[i]);  
    }  
    return 0;  
}