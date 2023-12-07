#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define MAX_LENGTH 100

char inputString[MAX_LENGTH];   // 全局变量用于线程间通信
int exitFlag = 0;     //    标记输入线程退出
int input_flag = 1;   // 标记输入还是打印，用于两个线程切换的标志

void *inputThread(void *arg) 
{
    while (1) {
        if (input_flag) {
        scanf("%s", inputString);

        // 如果输入字符串为 "q"，设置退出标志并退出线程
        if (strcmp(inputString, "q") == 0) {
            exitFlag = 1;
            break;
        }

        input_flag = 0; //输入结束，标记为0，打印线程开始打印
        }
    }

    pthread_exit(NULL);
}


void *printThread(void *arg) 
{
    while (1) {
        // 检查退出标志
        if (exitFlag) {
            break;
        }

        if(input_flag == 0) {
             // 打印输入字符串
             printf("Input String: %s\n", inputString);
             input_flag = 1;
        }

    }

    pthread_exit(NULL);
}

int main() 
{
    pthread_t tid_input, tid_print;

    // 创建两个线程
    if (pthread_create(&tid_input, NULL, inputThread, NULL) != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    if (pthread_create(&tid_print, NULL, printThread, NULL) != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    // 等待两个线程退出
    pthread_join(tid_input, NULL);
    pthread_join(tid_print, NULL);

    printf("Program Exiting\n");

    return 0;
}
