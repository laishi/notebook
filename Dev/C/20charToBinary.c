#include <stdio.h>

void charToBinary(char c) {
    for (int i = 7; i >= 0; --i) {
        // 利用位运算检查字符的每一位是否为1
        if ((c & (1 << i)) != 0) {
            printf("1");
        } else {
            printf("0");
        }
    }
    printf("\n");
}

int main() {
    char str = 'A'; // 字符'A'的ASCII码是65，二进制表示为01000001
    charToBinary(str);
    return 0;
}

