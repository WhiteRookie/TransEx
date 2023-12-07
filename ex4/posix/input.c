#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <pthread.h>

#define MAX_MSG_SIZE 1024

void* input_string(void* arg)
{
    mqd_t mqd = mq_open("/test.mq", O_CREAT | O_RDWR, 0666, NULL);
    if (mqd == -1) {
        perror("mq_open");
        exit(1);
    }

    while (1)
    {
        char* str;
        printf("Enter a string: ");
        fgets(str, MAX_MSG_SIZE, stdin);
        mq_send(mqd, str, MAX_MSG_SIZE, 0);
        if (str[0] == 'q') {
            break;
        }      
    }
    mq_close(mqd);
    mq_unlink("/test.mq");
    pthread_exit(NULL);

}

int main()
{
    pthread_t tid;

    pthread_create(&tid, NULL, input_string, NULL);
    pthread_join(tid, NULL);
    
    return 0;
}