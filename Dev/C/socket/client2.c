#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX_BUFFER_SIZE 1024

int main() {
    struct sockaddr_in serv_addr;
    int sock = 0, valread;
    char buffer[MAX_BUFFER_SIZE] = {0};
    const char *hello = "2号客服端: 白日依山尽 黄河入海流";

    sock = socket(AF_INET, SOCK_STREAM, 0);
    printf("客服端的文件描述符 = %d\n", sock);
    // 创建套接字
    if (sock < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // 将IPv4地址从文本转换为二进制形式
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    // 连接到服务器
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    // 发送消息给服务器
    send(sock, hello, strlen(hello), 0);
    printf("我是测试客服端1号选手\n");

    // 从服务器读取响应
    valread = read(sock, buffer, MAX_BUFFER_SIZE);
    printf("%s\n", buffer);

    return 0;
}
