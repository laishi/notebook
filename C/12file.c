#include <stdio.h>

int main() {
    // 打开文件以进行写操作
    FILE *filePtr = fopen("example.txt", "w");

    // 检查文件是否成功打开
    if (filePtr == NULL) {
        printf("Unable to open the file.\n");
        return 1;  // 返回非零值表示出错
    }

    // 写入数据到文件
    fprintf(filePtr, "Hello, File!\n");
    fprintf(filePtr, "This is a sample file.\n");

    // 关闭文件
    fclose(filePtr);

    // 打开文件以进行读操作
    filePtr = fopen("example.txt", "r");

    // 检查文件是否成功打开
    if (filePtr == NULL) {
        printf("Unable to open the file.\n");
        return 1;  // 返回非零值表示出错
    }

    // 读取文件内容
    char buffer[100];
    while (fgets(buffer, sizeof(buffer), filePtr) != NULL) {
        printf("%s", buffer);
    }

    // 关闭文件
    fclose(filePtr);

    return 0;  // 返回零值表示成功
}

