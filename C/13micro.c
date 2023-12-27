#include <stdio.h>

// 示例1：条件编译
#define DEBUG_MODE 1

#if DEBUG_MODE
#define DEBUG_PRINT(msg) printf("Debug: %s\n", msg)
#else
#define DEBUG_PRINT(msg)
#endif

// 示例2：宏参数和字符串连接
#define CONCAT(a, b) a ## b

// 示例3：包含头文件
#ifdef USE_MATH_FUNCTIONS
#include <math.h>
#endif

// 修改示例2的宏定义，支持多参数
#define STRINGIZE(...) #__VA_ARGS__

int main() {
    // 示例1：条件编译
    DEBUG_PRINT("This is a debug message.");

    // 示例2：宏参数和字符串连接
    int ab = CONCAT(10, 20);
    printf("Concatenated: %d\n", ab);

    // 示例3：包含头文件
    #ifdef USE_MATH_FUNCTIONS
        double squareRoot = sqrt(25.0);
        printf("Square root of 25: %f\n", squareRoot);
    #else
        printf("Math functions are not available.\n");
    #endif

    // 示例2：宏参数和字符串连接
    printf("Stringized: %s\n", STRINGIZE(Hello, World!));

    return 0;
}

