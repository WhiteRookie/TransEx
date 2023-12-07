#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024  // 共享内存的大小

int main() {
    key_t key = 1234;  // 用于标识共享内存段的键值
    int shmid;
    char *shmaddr;

    // 创建共享内存段
    if ((shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    // 将共享内存段连接到当前进程的地址空间
    if ((shmaddr = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    // 写入数据到共享内存
    strcpy(shmaddr, "Hello, shared memory!");

    // 从共享内存读取数据并输出
    printf("Data read from shared memory: %s\n", shmaddr);

    // 分离共享内存
    shmdt(shmaddr);

    return 0;
}
