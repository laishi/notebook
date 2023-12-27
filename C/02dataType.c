#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 函数声明
void exampleFunction();

// 全局常量
const int globalConstVar = 100;

// 全局静态变量
static int globalStaticVar = 50;

// 宏定义
#define MAX_SIZE 100
#define SQUARE(x) ((x) * (x))

// 宏函数
#define PRINT_MESSAGE(message) printf("Message: %s\n", message)

int main() {
    // 整数类型
    int integerVar = 10;                // sizeof(int) = 4 bytes
    short shortVar = 5;                  // sizeof(short) = 2 bytes
    long longVar = 1000;                 // sizeof(long) = 4 bytes (on most systems)
    long long longLongVar = 1000000;     // sizeof(long long) = 8 bytes

    // 无符号整数类型
    unsigned int unsignedIntVar = 15;    // sizeof(unsigned int) = 4 bytes

    // 浮点数类型
    float floatVar = 3.14;               // sizeof(float) = 4 bytes
    double doubleVar = 3.1415926535;     // sizeof(double) = 8 bytes

    // 字符类型
    char charVar = 'A';                   // sizeof(char) = 1 byte

    // 无符号字符类型
    unsigned char unsignedCharVar = 200;  // sizeof(unsigned char) = 1 byte

    // 数组
    int numbers[5] = {1, 2, 3, 4, 5};    // sizeof(numbers) = 20 bytes (5 * sizeof(int))
    
    // 字符数组
    char nameArray[] = "John";           // sizeof(nameArray) = 5 bytes (including null terminator)

    // 字符串常量
    const char* nameConstant = "John";   // sizeof(nameConstant) = 4 or 8 bytes (pointer size)

    // 字符串通过字符数组初始化
    char nameArrayInit[] = {'J', 'o', 'h', 'n', '\0'}; // sizeof(nameArrayInit) = 5 bytes

    // 字符串通过指针初始化，并使用malloc动态分配内存
    char* nameDynamic = (char*)malloc(strlen("John") + 1);  // +1 for null terminator
    strcpy(nameDynamic, "John");  // 使用strcpy复制字符串内容
    // sizeof(nameDynamic) 不是有效的方式获取动态分配字符串的大小

    // 结构体
    struct Point {
        int x;
        int y;
    };

    struct Point p1 = {10, 20};           // sizeof(struct Point) = 8 bytes (2 * sizeof(int))

    // 共用体
    union Data {
        int intValue;
        float floatValue;
    };

    union Data dataVar;                    // sizeof(union Data) = 4 bytes (size of the largest member)

    // 指针
    int num = 42;
    int *ptr = &num;                      // sizeof(int*) = 4 bytes or 8 bytes (depending on system architecture)

    // 枚举
    enum Color {RED, GREEN, BLUE};         // sizeof(enum Color) = 4 bytes (size of an int on most systems)
    enum Color chosenColor = BLUE;

    // 全局常量和全局静态变量
    printf("Global Constant Variable: %d\n", globalConstVar);
    printf("Global Static Variable: %d\n", globalStaticVar);

    // 局部常量和局部静态变量
    const int localConstVar = 10;
    static int localStaticVar = 20;

    printf("Local Constant Variable: %d\n", localConstVar);
    printf("Local Static Variable: %d\n", localStaticVar);

    // 输出整数类型变量
    printf("Integer Variable: %d\n", integerVar);
    printf("Size of int: %zu bytes\n", sizeof(int));

    // 输出无符号整数类型变量
    printf("Unsigned Integer Variable: %u\n", unsignedIntVar);
    printf("Size of unsigned int: %zu bytes\n", sizeof(unsigned int));

    // 输出浮点数类型变量
    printf("Float Variable: %.2f\n", floatVar);
    printf("Size of float: %zu bytes\n", sizeof(float));

    // 输出字符类型变量
    printf("Character Variable: %c\n", charVar);
    printf("Size of char: %zu bytes\n", sizeof(char));

    // 输出无符号字符类型变量
    printf("Unsigned Character Variable: %c\n", unsignedCharVar);
    printf("Size of unsigned char: %zu bytes\n", sizeof(unsigned char));

    // 输出数组元素
    printf("Array Elements: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");
    printf("Size of numbers array: %zu bytes\n", sizeof(numbers));

    // 输出字符数组
    printf("Name Array: %s\n", nameArray);
    printf("Size of nameArray: %zu bytes\n", sizeof(nameArray));

    // 输出字符串常量
    printf("Name Constant: %s\n", nameConstant);
    printf("Size of nameConstant: %zu bytes\n", sizeof(nameConstant));

    // 输出字符数组初始化的字符串
    printf("Name Array Initialized: %s\n", nameArrayInit);
    printf("Size of nameArrayInit: %zu bytes\n", sizeof(nameArrayInit));

    // 输出动态分配的字符串
    printf("Name Dynamic: %s\n", nameDynamic);
    // sizeof(nameDynamic) 不是有效的方式获取动态分配字符串的大小

    // 输出结构体变量
    printf("Struct Point: (%d, %d)\n", p1.x, p1.y);
    printf("Size of struct Point: %zu bytes\n", sizeof(struct Point));

    // 输出共用体变量
    dataVar.intValue = 42;
    printf("Value in Data Union: %d\n", dataVar.intValue);
    printf("Size of union Data: %zu bytes\n", sizeof(union Data));

    // 输出指针类型变量
    printf("Value at Pointer: %d\n", *ptr);
    printf("Size of int pointer: %zu bytes\n", sizeof(int*));

    // 输出枚举类型变量
    printf("Chosen Color: %d\n", chosenColor);
    printf("Size of enum Color: %zu bytes\n", sizeof(enum Color));

    // 使用宏定义的变量
    printf("Max Size: %d\n", MAX_SIZE);

    // 使用宏定义的函数
    int squareResult = SQUARE(5);
    printf("Square of 5: %d\n", squareResult);

    // 使用宏定义的函数打印消息
    PRINT_MESSAGE("Hello, Macros!");

    // 调用函数
    exampleFunction();

    // 释放动态分配的字符串内存
    free(nameDynamic);

    return 0;
}

// 函数定义
void exampleFunction() {
    printf("This is an example function.\n");
}

