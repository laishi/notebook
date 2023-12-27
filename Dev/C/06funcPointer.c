#include <stdio.h>

// 指针函数
int* square(int x) {
    static int result;  // 使用静态变量保存结果
    result = x * x;
    return &result;
}

// 函数指针
typedef int (*Operation)(int, int);

// 加法函数
int add(int a, int b) {
    return a + b;
}

// 减法函数
int subtract(int a, int b) {
    return a - b;
}

int main() {
    // 指针函数的调用
    int input = 5;
    int* squaredResult = square(input);
    printf("Square of %d: %d\n", input, *squaredResult);

    // 函数指针的使用
    Operation operation;  // 定义函数指针
    operation = add;  // 将函数指针指向加法函数
    int sum = operation(3, 4);
    printf("3 + 4 = %d\n", sum);

    operation = subtract;  // 将函数指针指向减法函数
    int difference = operation(7, 2);
    printf("7 - 2 = %d\n", difference);

    return 0;
}

