#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() 
{
    const char *pipePath = "/tmp/my_pipe"; // 命名管道路径
    int fd;
    char buffer[100];

    // 打开命名管道以进行读取
    fd = open(pipePath, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }
    while (1) {
        // 从命名管道中读取字符串
        read(fd, buffer, sizeof(buffer));
        if (buffer[0] == 'q') {
            break;
        }
        printf("Received: %s\n", buffer);
    }
    
    // 关闭命名管道
    close(fd);

    return 0;
}
