#include <arpa/inet.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h> // for time functions
#include <unistd.h>

#define DEFAULT_PORT 8080
#define PORT (argc > 1 ? atoi(argv[1]) : DEFAULT_PORT)

#define BUFFER_SIZE 1024

struct CookieData {
    char site[50];
    int id;
    char login[100];
};

void send_file(int client_socket, const char *file_path) {
    int file_descriptor = open(file_path, O_RDONLY);
    if (file_descriptor == -1) {
        perror("Error opening file");
        return;
    }
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;
    // Read and send the file in chunks
    while ((bytes_read = read(file_descriptor, buffer, sizeof(buffer))) > 0) {
        send(client_socket, buffer, bytes_read, 0);
    }
    // Close the file
    close(file_descriptor);
}

// 修改handle_request函数以设置Cookie

// Function to get the current date and time in HTTP format
void get_http_date(char *date_str, size_t date_str_size) {
    time_t current_time;
    struct tm *gmt_time;

    time(&current_time);
    gmt_time = gmtime(&current_time);

    strftime(date_str, date_str_size, "%a, %d %b %Y %H:%M:%S GMT", gmt_time);
}

void handle_request(int client_socket, struct CookieData *cookie_data) {
    char buffer[BUFFER_SIZE];
    ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
    if (bytes_received > 0) {
        const char *cookie_header = strstr(buffer, "Cookie:");

        /* if (cookie_header) { */
        /*     printf("cookie_header = %s\n", cookie_header); */
        /* } */

        // 解析HTTP请求，获取方法和路径
        char method[10], path[255];
        sscanf(buffer, "%s %s", method, path);
        int is_get = strcmp(method, "GET") == 0;
        char request_path[512] = "gald";

        if (strcmp(path, "/") == 0) {
            char *index = "/index.html";
            strcpy(path, index);
        }

        strcat(request_path, path);

        if (is_get) {
            char *content_type = "text/plain"; // 默认为纯文本
                                               // 根据文件扩展名设置不同的Content-Type
            char *file_extension = strrchr(request_path, '.');
            if (file_extension != NULL) {
                if (strcmp(file_extension, ".html") == 0) {
                    content_type = "text/html";
                    printf("buffer = %s\n", buffer);
                } else if (strcmp(file_extension, ".css") == 0) {
                    content_type = "text/css";
                } else if (strcmp(file_extension, ".js") == 0) {
                    content_type = "application/js";
                } else if (strcmp(file_extension, ".json") == 0) {
                    content_type = "application/json";
                } else if (strcmp(file_extension, ".jpg") == 0 ||
                        strcmp(file_extension, ".jpeg") == 0) {
                    content_type = "image/jpeg";
                } else if (strcmp(file_extension, ".png") == 0) {
                    content_type = "image/png";
                }
                // 添加其他文件类型的判断和设置
            }

            // 获取当前日期和时间
            char date_str[50];
            get_http_date(date_str, sizeof(date_str));

            // 构建响应头
            char response_header[512];
            snprintf(response_header, sizeof(response_header),
                    "HTTP/1.1 200 OK\r\n"
                    "Content-Type: %s\r\n"
                    "Date: %s\r\n",
                    content_type, date_str);

            // 设置Cookie，添加Max-Age字段使Cookie持久化
            snprintf(response_header + strlen(response_header),
                    sizeof(response_header) - strlen(response_header),
                    "Set-Cookie: site=%s; id=%d; login=%s; path=/; Max-Age=3600\r\n",
                    cookie_data->site, cookie_data->id, cookie_data->login);

            // 添加其他响应头
            // 示例：Last-Modified、Accept-Ranges、Content-Length
            // 在实际应用中，你需要根据文件的相关信息来设置这些头部字段
            snprintf(response_header + strlen(response_header),
                    sizeof(response_header) - strlen(response_header),
                    "Last-Modified: ...\r\n"
                    "Accept-Ranges: bytes\r\n"
                    "love: yes it is!\r\n"
                    "hi: hello world!\r\n"
                    "Content-Length: ...\r\n");

            // 结束响应头
            strcat(response_header, "\r\n");

            // 发送响应头
            send(client_socket, response_header, strlen(response_header), 0);

            // 发送文件内容
            send_file(client_socket, request_path);
        }
    }
    // 关闭客户端套接字
    close(client_socket);
}

// 处理客户端请求的线程函数
void *handle_client(void *arg) {
    int client_socket = *((int *)arg);
    free(arg); // 释放动态分配的内存

    // 创建CookieData结构体并填充数据
    struct CookieData my_cookie_data;
    strcpy(my_cookie_data.site, "gald");
    my_cookie_data.id = 385;
    strcpy(my_cookie_data.login, "你已经成功登录");

    // 处理客户端请求
    handle_request(client_socket, &my_cookie_data);

    return NULL;
}

int main(int argc, char *argv[]) {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    // 检查命令行参数是否正确
    if (argc > 2) {
        fprintf(stderr, "Usage: %s [port]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Create socket
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Set up server address struct
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORT);

    // Bind socket
    if (bind(server_socket, (struct sockaddr *)&server_addr,
                sizeof(server_addr)) == -1) {
        perror("Error binding socket");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_socket, 10) == -1) {
        perror("Error listening for connections");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on http://127.0.0.1:%d\n", PORT);

    while (1) {
        // Accept a client connection
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr,
                &client_addr_len);
        if (client_socket == -1) {
            perror("Error accepting connection");
            continue;
        }

        // 为新的连接创建一个线程来处理
        pthread_t *thread = malloc(sizeof(pthread_t));
        if (thread == NULL) {
            perror("Error allocating memory for thread");
            close(client_socket);
            continue;
        }

        int *client_socket_ptr = malloc(sizeof(int));
        if (client_socket_ptr == NULL) {
            perror("Error allocating memory for client socket");
            free(thread);
            close(client_socket);
            continue;
        }

        *client_socket_ptr = client_socket;

        if (pthread_create(thread, NULL, handle_client, client_socket_ptr) != 0) {
            perror("Error creating thread");
            free(thread);
            free(client_socket_ptr);
            close(client_socket);
        }

        // 主线程不等待子线程，继续处理下一个连接
        pthread_detach(*thread);
    }

    // 关闭服务器套接字
    close(server_socket);

    return 0;
}
