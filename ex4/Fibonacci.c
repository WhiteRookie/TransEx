#include <stdio.h>

int Fibonacci(int n);

int main() 
{
    int n;

    printf("Enter the length of the Fibonacci sequence: ");
    scanf("%d", &n);
    if (n <= 0) {
        printf("Invalid input.\n");
    }
    for (int i = 0; i < n; i++) {
        printf("%d ", Fibonacci(i));
    }
    
    return 0;
}


// 生成斐波那契数列的函数
int Fibonacci(int n) 
{
    if (n == 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    } else {
        return Fibonacci(n - 1) + Fibonacci(n - 2);
    }
}
