#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>
#include <unistd.h>

int main() {
    const char* SHM_NAME = "/test_shm";
    const int SHM_SIZE = 1024;
    
    // 打开共享内存对象
    int shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }
    
    // 将共享内存对象映射到进程地址空间
    char* ptr = (char*)mmap(0, SHM_SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }
    
    // 获取标志
    int* flag = (int*)ptr;
    
    while (1) {
        if (*flag == 1) {
            if (strcmp(ptr + sizeof(int), "q\n") == 0) {
                break;
            } else {
                printf("Received: %s", ptr + sizeof(int));
                *flag = 0;  // 重置标志
            }
        }
    }
    
    // 解除映射
    munmap(ptr, SHM_SIZE);
    
    // 关闭共享内存对象
    close(shm_fd);
    
    return 0;
}
