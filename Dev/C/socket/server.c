#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX_BUFFER_SIZE 1024

void handle_client(int client_socket) {
    char buffer[MAX_BUFFER_SIZE];
    ssize_t bytes_received;

    while ((bytes_received = recv(client_socket, buffer, sizeof(buffer), 0)) > 0) {
        buffer[bytes_received] = '\0';  // 确保接收到的数据以 null 结尾

        // 打印收到的消息
        printf("收到客户端的消息: %s\n", buffer);

        // 回复客户端
        char reply[MAX_BUFFER_SIZE];
        snprintf(reply, sizeof(reply), "回复客户端: %s", buffer);
        send(client_socket, reply, strlen(reply), 0);
        printf("回复客户端: %s\n", buffer);
    }

    if (bytes_received == 0) {
        printf("客户端关闭连接\n");
    } else {
        perror("recv");
    }

    close(client_socket);
}

int main() {
    int server_fd, client_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_fd == -1) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) == -1) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 5) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("服务器等待连接...\n");

    while (1) {
        if ((client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        printf("有新连接，处理中...\n");
        handle_client(client_socket);
    }

    return 0;
}

