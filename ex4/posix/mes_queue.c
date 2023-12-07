#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

#define QUEUE_NAME "/test.mq"
#define MAX_MSG_SIZE 1024
#define MSG_BUFFER_SIZE (MAX_MSG_SIZE + 1)

int main() {
    mqd_t mqd;  // 消息队列描述符
    struct mq_attr attr;
    char buffer[MSG_BUFFER_SIZE];

    // 创建消息队列
    mqd = mq_open(QUEUE_NAME, O_CREAT | O_RDWR, 0666, NULL);
    if (mqd == -1) {
        perror("mq_open");
        return -1;
    }

    // 获取消息队列属性
    mq_getattr(mqd, &attr);
    printf("mq_flags: %ld\n", attr.mq_flags);
    printf("mq_maxmsg: %ld\n", attr.mq_maxmsg);
    printf("mq_msgsize: %ld\n", attr.mq_msgsize);
    printf("mq_curmsgs: %ld\n", attr.mq_curmsgs);

    // 发送消息
    const char* message = "Hello, Message Queue!";
    int ret = mq_send(mqd, message, strlen(message) + 1, 0);
    if (ret == -1) {
        perror("mq_send");
        mq_close(mqd);
        mq_unlink(QUEUE_NAME);
        return -1;
    }
    printf("Message sent: %s\n", message);

    // 接收消息
    ssize_t bytes_read = mq_receive(mqd, buffer, MSG_BUFFER_SIZE, NULL);
    if (bytes_read == -1) {
        perror("mq_receive");
        mq_close(mqd);
        mq_unlink(QUEUE_NAME);
        return -1;
    }
    buffer[bytes_read] = '\0';
    printf("Message received: %s\n", buffer);

    // 关闭消息队列
    mq_close(mqd);

    // 删除消息队列
    mq_unlink(QUEUE_NAME);

    return 0;
}
