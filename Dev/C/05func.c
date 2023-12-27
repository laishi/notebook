#include <stdio.h>

// 函数的声明
void greet();
int add(int a, int b);
int factorial(int n);

int main() {
    // 函数的调用
    greet();

    // 调用带有参数和返回值的函数
    int sumResult = add(3, 7);
    printf("Sum: %d\n", sumResult);

    // 调用递归函数
    int factorialResult = factorial(5);
    printf("Factorial of 5: %d\n", factorialResult);

    return 0;
}

// 函数的定义
void greet() {
    printf("Hello, World!\n");
}

// 带有参数和返回值的函数
int add(int a, int b) {
    return a + b;
}

// 递归函数计算阶乘
int factorial(int n) {
    // 基本情况
    if (n == 0 || n == 1) {
        return 1;
    } else {
        // 递归调用
        return n * factorial(n - 1);
    }
}

