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


void* input_string(void* arg)
{
    key_t key;
    int msgid;
    struct message msg;

    // 生成唯一的key值
    key = ftok(".", 'm');
    // 创建消息队列
    msgid = msgget(key, IPC_CREAT | 0666);
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    while (1) {
        printf("Enter a string (q to quit): ");
        fgets(msg.mtext, MAX_MESSAGE_SIZE, stdin);
        msg.mtype = 1;
        msgsnd(msgid, &msg, sizeof(struct message) - sizeof(long), 0); //将数据发送到消息队列
        if (strcmp(msg.mtext, "q\n") == 0) {
            break;
        }
    }
    // 删除消息队列
    msgctl(msgid, IPC_RMID, NULL);
    pthread_exit(NULL);  
    return 0;
}

int main() 
{
    pthtead_t tid;
    if(pthread_create(&tid, NULL, input_string, NULL) != 0) {
        perror("pthread_create");
        exit(1);
    }
   
    pthread_join(tid, NULL);

    printf("input Process exit\n");

    return 0;
}
