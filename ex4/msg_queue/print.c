#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <pthread.h>

#define MAX_MESSAGE_SIZE 100

// 定义消息结构体
struct message {
    long mtype;
    char mtext[MAX_MESSAGE_SIZE];
};

void* print_message(void* arg) 
{
    key_t key;
    int msgid;
    struct message msg;

    // 生成唯一的key值
    key = ftok(".", 'm');
    // 获取消息队列
    msgid = msgget(key, 0666);
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    while (1) {
        msgrcv(msgid, &msg, sizeof(struct message) - sizeof(long), 1, 0);
        if (strcmp(msg.mtext, "q\n") == 0) {
            break;
        }
        printf("Received: %s", msg.mtext);
    }
    pthread_exit(NULL);
    return 0;
}

int main() 
{
    pthread_t tid;
    pthread_create(&tid, NULL, print_message, NULL);
    pthread_join(tid, NULL);
    printf("print process exit\n");

    return 0;
}
