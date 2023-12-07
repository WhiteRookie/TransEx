#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
    pid_t child_pid;

    int pipe_fd[2];  // 管道描述符
    if (pipe(pipe_fd) < 0) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    
    // 创建子进程
    child_pid = fork();
    if(child_pid < 0) {
        printf("create child process failed\n");
    }

    while (1) {
        if (child_pid == 0) {
            // 子进程
            close(pipe_fd[0]); // 关闭读端
            char inuputString[100];
            scanf("%s", inuputString);
            if (strcmp(inuputString, "q") == 0) {
                close(pipe_fd[1]); // 关闭写端
                exit(0);
                break;
            }
            write(pipe_fd[1], inuputString, 100);
        }else {
            int status;
            waitpid(child_pid, &status, 0);
            if (status == 0) {
                break;
            } else {
                close(pipe_fd[1]); // 关闭写端
                char inuputString[100];
                read(pipe_fd[0], inuputString, 100);
                printf("Input String: %s\n", inuputString);
            }
        }
        
    }

    return 0;
}        
   