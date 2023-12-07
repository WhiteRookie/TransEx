#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_PORT 8888

int main() {
    int sockfd, newsockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len;
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
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    // 绑定到指定端口
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Failed to bind");
        exit(EXIT_FAILURE);
    }

    // 监听连接请求
    if (listen(sockfd, 5) == -1) {
        perror("Failed to listen");
        exit(EXIT_FAILURE);
    }

    printf("Waiting for client connection...\n");

    // 接受客户端连接
    client_len = sizeof(client_addr);
    newsockfd = accept(sockfd, (struct sockaddr *)&client_addr, &client_len);
    if (newsockfd == -1) {
        perror("Failed to accept");
        exit(EXIT_FAILURE);
    }

    printf("Client connected\n");

    // 接收客户端数据
    memset(buffer, 0, sizeof(buffer));
    if (recv(newsockfd, buffer, sizeof(buffer)-1, 0) == -1) {
        perror("Failed to receive data");
        exit(EXIT_FAILURE);
    }
    printf("Received data from client: %s\n", buffer);

    // 发送响应给客户端
    strcpy(buffer, "Hello from server");
    if (send(newsockfd, buffer, strlen(buffer), 0) == -1) {
        perror("Failed to send data");
        exit(EXIT_FAILURE);
    }

    // 关闭连接
    close(newsockfd);
    close(sockfd);

    return 0;
}
