#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>

void sendFile(int clientSocket, const char *filePath) {
  char fullFilePath[255] = ".";
  strcat(fullFilePath, filePath);

  FILE *file = fopen(fullFilePath, "r");

  if (!file) {
    const char *response = "HTTP/1.1 404 Not Found\r\n"
                           "\r\n"
                           "404 Not Found\n";
    send(clientSocket, response, strlen(response), 0);
    return;
  }

  fseek(file, 0, SEEK_END);
  long fileSize = ftell(file);
  fseek(file, 0, SEEK_SET);

  char *fileContent = malloc(fileSize + 1);
  if (!fileContent) {
    perror("Error allocating memory");
    fclose(file);
    close(clientSocket);
    return;
  }

  fread(fileContent, 1, fileSize, file);
  fclose(file);

  fileContent[fileSize] = '\0';

  const char *responseFormat = "HTTP/1.1 200 OK\r\n"
                               "Content-Length: %ld\r\n"
                               "\r\n"
                               "%s";
  char response[1024];
  sprintf(response, responseFormat, fileSize, fileContent);

  send(clientSocket, response, strlen(response), 0);

  free(fileContent);
}

void handleHttpRequest(int clientSocket) {
  char buffer[1024];
  ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);

  if (bytesRead < 0) {
    perror("Error reading from socket");
    close(clientSocket);
    return;
  }

  char method[10], path[255];
  sscanf(buffer, "%s %s", method, path);

  printf("Received HTTP request:\n%s\n", buffer);

  if (strcmp(method, "GET") == 0) {
    printf("PATH: \n%s\n", path);
    if (strcmp(path, "/") == 0) {
      sendFile(clientSocket, "index.html");
    } else {
      sendFile(clientSocket, path);
    }
  }

  close(clientSocket);
}

void socketServer(const char *ip, int port) {
  int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (serverSocket == -1) {
    perror("Error creating socket");
    exit(EXIT_FAILURE);
  }

  struct sockaddr_in serverAddr = {.sin_family = AF_INET,
                                   .sin_port = htons(port),
                                   .sin_addr.s_addr = inet_addr(ip)};
  if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) ==
      -1) {
    perror("Error binding socket");
    close(serverSocket);
    exit(EXIT_FAILURE);
  }

  if (listen(serverSocket, 10) == -1) {
    perror("Error listening on socket");
    close(serverSocket);
    exit(EXIT_FAILURE);
  }

  while (1) {
    struct sockaddr_in clientAddr;
    socklen_t clientAddrSize = sizeof(clientAddr);
    int clientSocket =
        accept(serverSocket, (struct sockaddr *)&clientAddr, &clientAddrSize);

    if (clientSocket != -1) {
      handleHttpRequest(clientSocket);
    }
  }

  close(serverSocket);
}

int main(int argc, char *argv[]) {
  const char *ip = "127.0.0.1";
  int port = 8080;
  printf("http://%s:%i\n", ip, port);

  socketServer(ip, port);

  return 0;
}
