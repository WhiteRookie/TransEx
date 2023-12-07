#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>

int main() 
{   
    int pipe_fd[2];  // 管道描述符
    if (pipe(pipe_fd) < 0) {
        printf("create pipe failed\n");
        exit(1);
    }

    pid_t child_pid;
    // 创建子进程
    child_pid = fork();
    if (child_pid < 0) {
        printf("create child process failed\n");
        exit(1);
    }

    if (child_pid == 0) {  // 子进程
        while (1) {
            char prt_buf[100];
            close(pipe_fd[1]); // 关闭写端
            read(pipe_fd[0], prt_buf, 100);
            if (strcmp(prt_buf, "q") == 0) {
                close(pipe_fd[0]); // 关闭读端
                exit(0);
                break;
            }else {
                printf("Received: %s\n", prt_buf);
            }
        }
        exit(0);
    }else {  // 父进程
        while (1) {
        char inputString[100];
        printf("Enter a string: ");
        scanf("%s", inputString);
        write(pipe_fd[1], inputString, 100);  //父进程写入数据
        if (strcmp(inputString, "q") == 0) {
            close(pipe_fd[1]); // 关闭写端
            break;
        }
    }

   

    // 等待子进程结束
    wait(NULL);

    return 0;
}
