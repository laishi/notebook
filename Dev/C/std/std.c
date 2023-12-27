#include <stdio.h>    // 位置：/usr/include/stdio.h
#include <stdlib.h>   // 位置：/usr/include/stdlib.h
#include <string.h>   // 位置：/usr/include/string.h
#include <math.h>     // 位置：/usr/include/math.h
#include <time.h>     // 位置：/usr/include/time.h
#include <ctype.h>    // 位置：/usr/include/ctype.h
#include <stddef.h>   // 位置：/usr/include/stddef.h
#include <stdbool.h>  // 位置：/usr/include/stdbool.h
#include <stdarg.h>   // 位置：/usr/include/stdarg.h
#include <assert.h>   // 位置：/usr/include/assert.h

int main() {
    // stdio.h
    printf("Hello, World!\n");  // 输出到标准输出
    int num;
    scanf("%d", &num);    // 从标准输入读取整数
    getchar();            // 读取并忽略一个字符
    putchar('A');         // 将字符 'A' 输出到标准输出

    FILE *file = fopen("example.txt", "w");  // 打开文件用于写入
    if (file != NULL) {
        fprintf(file, "This is a file example.");  // 将内容写入文件
        fclose(file);  // 关闭文件
    }

    // stdlib.h
    int* arr = (int*)malloc(5 * sizeof(int));  // 分配动态内存
    free(arr);  // 释放动态内存
    int* newArr = (int*)calloc(10, sizeof(int));  // 分配并清零
    newArr = (int*)realloc(newArr, 20 * sizeof(int));  // 调整动态内存大小
    srand(time(NULL));  // 使用当前时间设置随机数种子
    int randomNum = rand();  // 生成伪随机数
    exit(0);  // 程序正常退出

    // string.h
    char str1[] = "Hello";
    char str2[] = " World";
    char result[50];
    strcpy(result, str1);  // 复制字符串
    strcat(result, str2);  // 拼接字符串
    int compareResult = strcmp(str1, str2);  // 比较字符串
    size_t length = strlen(result);  // 获取字符串长度
    char* foundChar = strchr(result, 'o');  // 在字符串中查找字符
    char* foundStr = strstr(result, "World");  // 在字符串中查找子字符串

    // math.h
    double sineValue = sin(30);  // 计算正弦值
    double squareRoot = sqrt(25);  // 计算平方根
    double powerResult = pow(2, 3);  // 计算指数
    double absoluteValue = fabs(-7.5);  // 计算绝对值

    // time.h
    time_t currentTime = time(NULL);  // 获取当前时间
    char* timeString = ctime(&currentTime);  // 将时间转换为字符串
    double difference = difftime(currentTime, currentTime - 3600);  // 计算时间差
    clock_t clockTicks = clock();  // 获取时钟计时
    struct tm* timeInfo;
    char timeBuffer[80];
    time(&currentTime);
    timeInfo = localtime(&currentTime);
    strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", timeInfo);  // 格式化时间

    // ctype.h
    char character = 'A';
    int isAlpha = isalpha(character);  // 判断是否为字母
    int isDigit = isdigit(character);  // 判断是否为数字
    int isLower = islower(character);  // 判断是否为小写字母
    int toUpper = toupper(character);  // 转换为大写字母
    int toLower = tolower(character);  // 转换为小写字母

    // stddef.h
    size_t size = sizeof(int);  // 获取类型的大小
    int* nullPointer = NULL;  // 空指针

    // stdbool.h
    bool booleanValue = true;  // 布尔类型
    bool trueValue = true;  // 真值
    bool falseValue = false;  // 假值

    // stdarg.h
    char* format = "%d %s %f";
    va_list args;
    va_start(args, format);
    int arg1 = va_arg(args, int);
    char* arg2 = va_arg(args, char*);
    double arg3 = va_arg(args, double);
    va_end(args);

    // assert.h
    assert(1 == 1);  // 断言

    return 0;
}

