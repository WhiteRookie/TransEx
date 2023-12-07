#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() 
{
    const char *pipePath = "/tmp/my_pipe"; // 命名管道路径
    int fd;

    // 创建命名管道
    mkfifo(pipePath, 0666);

    // 打开命名管道以进行写入
    fd = open(pipePath, O_WRONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }
    while (1)
    {
        // 从键盘读取字符串并写入命名管道
        char input[100];
        printf("Enter a string: ");
        fgets(input, sizeof(input), stdin);
        write(fd, input, sizeof(input));
        if (input[0] == 'q') {
            break;
        }
    }
    
    // 关闭命名管道
    close(fd);

    return 0;
}
