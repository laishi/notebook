#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HEADERS 20

typedef struct {
    char method[20];
    char path[100];
    char http_version[20];
    char* headers[MAX_HEADERS][2];
    int num_headers;
} HttpRequest;

void parse_http_request(const char* msg, HttpRequest* request) {
    char* lines[MAX_HEADERS];
    char* token;

    // Tokenize the input string into lines
    int i = 0;
    token = strtok((char*)msg, "\n");
    while (token != NULL) {
        lines[i++] = token;
        token = strtok(NULL, "\n");
    }

    // Parse request line
    sscanf(lines[0], "%s %s %s", request->method, request->path, request->http_version);

    // Parse headers
    request->num_headers = 0;
    for (int j = 1; j < i && request->num_headers < MAX_HEADERS; j++) {
        if (strlen(lines[j]) > 0) {
            char* name = strtok(lines[j], ": ");
            char* value = strtok(NULL, ": ");
            request->headers[request->num_headers][0] = strdup(name);
            request->headers[request->num_headers][1] = strdup(value);
            request->num_headers++;
        }
    }
}

void print_http_request(const HttpRequest* request) {
    printf("Method: %s\n", request->method);
    printf("Path: %s\n", request->path);
    printf("HTTP Version: %s\n", request->http_version);

    printf("Headers:\n");
    for (int i = 0; i < request->num_headers; i++) {
        printf("%s: %s\n", request->headers[i][0], request->headers[i][1]);
    }
}

void free_http_request(HttpRequest* request) {
    // Free allocated memory for headers
    for (int i = 0; i < request->num_headers; i++) {
        if (request->headers[i][0] != NULL) {
            free(request->headers[i][0]);
        }
        if (request->headers[i][1] != NULL) {
            free(request->headers[i][1]);
        }
    }
}

int main() {
    const char* msg = "GET / HTTP/1.1\n\
                      Host: localhost:8080\n\
                      Connection: keep-alive\n\
                      Cache-Control: max-age=0\n\
                      sec-ch-ua: \"Not_A Brand\";v=\"8\", \"Chromium\";v=\"120\", \"Microsoft Edge\";v=\"120\"\n\
                      sec-ch-ua-mobile: ?0\n\
                      sec-ch-ua-platform: \"Windows\"\n\
                      Upgrade-Insecure-Requests: 1\n\
                      User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36 Edg/120.0.0.0\n\
                      Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7\n\
                      Sec-Fetch-Site: none\n\
                      Sec-Fetch-Mode: navigate\n\
                      Sec-Fetch-User: ?1\n\
                      Sec-Fetch-Dest: document\n\
                      Accept-Encoding: gzip, deflate, br\n\
                      Accept-Language: zh-CN,zh;q=0.9,en;q=0.8,en-GB;q=0.7,en-US;q=0.6";

    HttpRequest request;
    parse_http_request(msg, &request);
    print_http_request(&request);

    // Free allocated memory
    free_http_request(&request);

    return 0;
}

