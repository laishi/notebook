#include <stdio.h>
#include <string.h>

void charToBinary(char c) {
    // 将字符转换为二进制
    for (int i = 7; i >= 0; i--) {
        printf("%d", (c >> i) & 1);
    }
    printf("\n");
}

int main() {
    char buffer[14];
    
    // 使用sprintf将字符串格式化写入缓冲区
    sprintf(buffer, "Hello, %s!", "World");

    for (int i = 0; i < 14; ++i) {
      charToBinary(buffer[i]);
    }
    
    // 打印缓冲区中的字符串
    printf("String: %s\n", buffer);

    return 0;
}

