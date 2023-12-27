#include <stdio.h>

int main() {
    printf("+--------+--------+\n");
    printf("| ASCII  | Char   |\n");
    printf("+--------+--------+\n");

    for (int i = 0; i < 128; ++i) {
        // 使用-左对齐，3表示宽度为3
        printf("| %-6d |   '%c'  |\n", i, (char)i);
    }

    printf("+--------+--------+\n");

    return 0;
}

