#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8888

int main() 
{
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[1024];

    // 创建 socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("Failed to create socket");
        exit(EXIT_FAILURE);
    }

    // 设置服务器地址信息
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
        perror("Invalid address/Address not supported");
        exit(EXIT_FAILURE);
    }

    // 连接到服务器
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Failed to connect");
        exit(EXIT_FAILURE);
    }

    // 发送数据
    strcpy(buffer, "Hello from client");
    if (send(sockfd, buffer, strlen(buffer), 0) == -1) {
        perror("Failed to send data");
        exit(EXIT_FAILURE);
    }

    // 接收服务器响应
    memset(buffer, 0, sizeof(buffer));
    if (recv(sockfd, buffer, sizeof(buffer)-1, 0) == -1) {
        perror("Failed to receive data");
        exit(EXIT_FAILURE);
    }
    printf("Received response from server: %s\n", buffer);

    // 关闭 socket
    close(sockfd);

    return 0;
}
