#include <stdio.h>

//FILE PRINT FORMAT

int dio() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    printf("You entered: %d\n", num);
}


int fio() {
    int num;
    fprintf(stdout, "Enter a number: ");
    fscanf(stdin, "%d", &num);
    fprintf(stdout, "You entered: %d\n", num);
}

int main() {

    dio();
    fio();

    return 0;
}


