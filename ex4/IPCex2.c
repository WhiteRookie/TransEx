#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSG_SIZE 256

// 定义消息结构体
struct message {
    long mtype;  // 消息类型
    char mtext[MSG_SIZE];  // 消息内容
};

// 消息队列标识符
int msqid;

// 读取输入的线程函数
void* read_input(void* arg) {
    struct message msg;
    msg.mtype = 1;  // 消息类型为1

    while(1) {
        printf("Enter a string: ");
        fgets(msg.mtext, sizeof(msg.mtext), stdin);

        // 去掉换行符
        size_t len = strlen(msg.mtext);
        if (len > 0 && msg.mtext[len - 1] == '\n') {
            msg.mtext[len - 1] = '\0';
        }

        // 发送消息到消息队列
        if (msgsnd(msqid, &msg, sizeof(msg.mtext), 0) == -1) {
            perror("msgsnd");
            exit(1);
        }

        // 判断是否退出循环
        if (strcmp(msg.mtext, "q") == 0) {
            break;
        }

    }

    pthread_exit(NULL);
}

// 打印消息的线程函数
void* print_message(void* arg) {
    struct message msg;

    while (1) {
        // 接收消息
        if (msgrcv(msqid, &msg, sizeof(msg.mtext), 1, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }

        // 判断是否退出循环
        if (strcmp(msg.mtext, "q") == 0) {
            break;
        }

        // 打印消息内容
        printf("Received message: %s\n", msg.mtext);
    }

    pthread_exit(NULL);
}

int main() {
    key_t key = 1234;  // 用于标识消息队列的键值
    pthread_t tid_read, tid_print;

    // 创建消息队列
    if ((msqid = msgget(key, IPC_CREAT | 0666)) == -1) {
        perror("msgget");
        exit(1);
    }

    // 创建读取输入的线程
    if (pthread_create(&tid_read, NULL, read_input, NULL) != 0) {
        perror("pthread_create");
        exit(1);
    }

    // 创建打印消息的线程
    if (pthread_create(&tid_print, NULL, print_message, NULL) != 0) {
        perror("pthread_create");
        exit(1);
    }

    // 等待读取输入的线程结束
    if (pthread_join(tid_read, NULL) != 0) {
        perror("pthread_join");
        exit(1);
    }

    // 等待打印消息的线程结束
    if (pthread_join(tid_print, NULL) != 0) {
        perror("pthread_join");
        exit(1);
    }

    // 删除消息队列
    if (msgctl(msqid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(1);
    }

    return 0;
}
