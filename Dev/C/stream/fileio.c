#include <stdio.h>

int main() {
    FILE *file;
    char data[10000];

    // Writing to a file
    /* file = fopen("example.txt", "w"); */
    /* fprintf(file, "Hello, file I/O!\n"); */
    /* fclose(file); */

    // Reading from a file
    file = fopen("example.txt", "r");

    if (file != NULL) {
        while (fgets(data, sizeof(data), file) != NULL) {
            printf("%s", data);
        }

        fclose(file);
    } else {
        printf("File not found.\n");
    }

    return 0;
}

