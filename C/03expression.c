// arithmetic_and_logic_operations.c

#include <stdio.h>

// 函数声明
void exampleFunction();

int main() {
    // 算术运算符
    int a = 10, b = 4;
    int sum = a + b;    // 加法
    int difference = a - b;    // 减法
    int product = a * b;    // 乘法
    int quotient = a / b;    // 除法
    int remainder = a % b;   // 取余

    printf("Sum: %d\n", sum);
    printf("Difference: %d\n", difference);
    printf("Product: %d\n", product);
    printf("Quotient: %d\n", quotient);
    printf("Remainder: %d\n", remainder);

    // 关系运算符
    int x = 5, y = 10;

    printf("%d == %d is %d\n", x, y, x == y);
    printf("%d != %d is %d\n", x, y, x != y);
    printf("%d < %d is %d\n", x, y, x < y);
    printf("%d > %d is %d\n", x, y, x > y);
    printf("%d <= %d is %d\n", x, y, x <= y);
    printf("%d >= %d is %d\n", x, y, x >= y);

    // 逻辑运算符
    int m = 5, n = 10;

    printf("(m > 0) && (n > 0) is %d\n", (m > 0) && (n > 0));  // 逻辑与
    printf("(m > 0) || (n > 0) is %d\n", (m > 0) || (n > 0));  // 逻辑或
    printf("!(m > 0) is %d\n", !(m > 0));  // 逻辑非

    // 表达式和运算符优先级
    int p = 5, q = 10, r = 15;

    int result = p + q * r;  // 乘法的优先级高于加法
    int anotherResult = (p + q) * r;  // 使用括号改变优先级

    printf("Result: %d\n", result);
    printf("Another Result: %d\n", anotherResult);

    // 调用函数
    exampleFunction();

    return 0;
}

// 函数定义
void exampleFunction() {
    printf("This is an example function.\n");
}

