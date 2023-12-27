//gcc main.c myMath.c -o math
#include <stdio.h>
#include "myMath.h"

int main() {
    int a = 5, b = 3;

    printf("Addition: %d\n", add(a, b));
    printf("Subtraction: %d\n", subtract(a, b));
    printf("Multiplication: %d\n", multiply(a, b));
    printf("Division: %.2f\n", divide(a, b));

    return 0;
}

