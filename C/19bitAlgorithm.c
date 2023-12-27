#include <stdio.h>

int main() {
    unsigned int a = 5;  // 二进制：0101
    unsigned int b = 3;  // 二进制：0011
    unsigned int result;

    // 位与（&）
    result = a & b;
    printf("Bitwise AND: %u\n", result);  // 二进制：0001，结果为1

    // 位或（|）
    result = a | b;
    printf("Bitwise OR: %u\n", result);   // 二进制：0111，结果为7

    // 位异或（^）
    result = a ^ b;
    printf("Bitwise XOR: %u\n", result);  // 二进制：0110，结果为6

    // 取反（~）
    result = ~a;
    printf("Bitwise NOT: %u\n", result);  // 二进制：1010，结果为10

    // 左移（<<）
    result = a << 2;
    printf("Left Shift: %u\n", result);   // 左移2位，结果为20（二进制：10100）

    // 右移（>>）
    result = a >> 1;
    printf("Right Shift: %u\n", result);  // 右移1位，结果为2（二进制：0010）

    return 0;
}

