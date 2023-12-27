#include <stdio.h>
#include <string.h>

// Define union
union MyUnion {
    int intValue;
    float floatValue;
    char stringValue[20];
};

int main() {
    // Declare union variable
    union MyUnion myUnion;

    // Assign values to union members
    myUnion.intValue = 42;
    printf("Integer Value: %d\n", myUnion.intValue);

    myUnion.floatValue = 3.14;
    printf("Float Value: %.2f\n", myUnion.floatValue);

    // Use strcpy after including the <string.h> header
    strcpy(myUnion.stringValue, "Hello, Union!");
    printf("String Value: %s\n", myUnion.stringValue);

    // Size of the union is equal to the size of its largest member
    printf("Size of MyUnion: %lu bytes\n", sizeof(union MyUnion));

    return 0;
}

