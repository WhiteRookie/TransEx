#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define SHM_KEY 12345
#define BUFFER_SIZE 256

struct shared_memory {
    int input_flag;  // 输入标志位，0表示没有新的输入，1表示有新的输入
    char buffer[BUFFER_SIZE];  // 存储输入数据的缓冲区
};

int main() 
{
    int shmid;
    struct shared_memory *shared_mem;

    // 创建共享内存段
    shmid = shmget(SHM_KEY, sizeof(struct shared_memory), IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    // 连接到共享内存段
    shared_mem = (struct shared_memory *)shmat(shmid, NULL, 0);
    if (shared_mem == (void *)-1) {
        perror("shmat");
        exit(1);
    }

    while (1) {
        // 等待输入程序产生新的数据
        while (shared_mem->input_flag == 0) {
            usleep(1000);
        }
        if (shared_mem->buffer[0] == 'q') {
            break;
        }
        
        printf("Received: %s", shared_mem->buffer);

        // 设置输入标志位为0，表示已经消费完数据
        shared_mem->input_flag = 0;
    }

    // 解除连接共享内存段
    shmdt(shared_mem);

    // 删除共享内存段
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
