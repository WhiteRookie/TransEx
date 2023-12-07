#include <stdio.h>

int search(int arr[], int size, int key) 
{
    int left = 0;
    int right = size - 1;

    while(left <= right) {
        int mid = left + (right - left) / 2;
        if(arr[mid] == key)
            return mid;
        else if(arr[mid] > key)
            right = mid - 1;
        else if(arr[mid] < key)
            left = mid + 1;
    }
    return -1;
}

int main() 
{
    int arr[] = {1, 21, 34, 65, 88, 192, 212, 287};  // 有序数组
    int size = sizeof(arr) / sizeof(arr[0]);
    int pos = search(arr, size, 100);

    if (pos != -1) {
        printf("The element is found at index: %d\n", pos);
    } else {
        printf("Element not found in the array.\n");
    }

    return 0;
}
