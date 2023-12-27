#include <stdio.h>

// 定义错误码
#define SUCCESS 0
#define ERROR_DIVIDE_BY_ZERO -1
#define ERROR_NEGATIVE_RESULT -2

// 函数声明
int divide(int a, int b, int *result);

int main() {
    int a = 10, b = 2, result;

    // 调用函数并检查错误码
    int errorCode = divide(a, b, &result);

    // 处理错误
    if (errorCode == SUCCESS) {
        printf("Division result: %d\n", result);
    } else if (errorCode == ERROR_DIVIDE_BY_ZERO) {
        printf("Error: Divide by zero!\n");
    } else if (errorCode == ERROR_NEGATIVE_RESULT) {
        printf("Error: Negative result!\n");
    } else {
        printf("Unknown error!\n");
    }

    return 0;
}

// 函数实现，使用错误码进行错误处理
int divide(int a, int b, int *result) {
    if (b == 0) {
        return ERROR_DIVIDE_BY_ZERO;
    }

    *result = a / b;

    if (*result < 0) {
        return ERROR_NEGATIVE_RESULT;
    }

    return SUCCESS;
}

