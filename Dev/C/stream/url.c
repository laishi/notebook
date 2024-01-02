#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to decode URL-encoded string
void urldecode(char *dst, const char *src) {
    char a, b;
    while (*src) {
        if ((*src == '%') &&
            ((a = src[1]) && (b = src[2])) &&
            (isxdigit(a) && isxdigit(b))) {
            if (a >= 'a')
                a -= 'a'-'A';
            if (a >= 'A')
                a -= ('A' - 10);
            else
                a -= '0';
            if (b >= 'a')
                b -= 'a'-'A';
            if (b >= 'A')
                b -= ('A' - 10);
            else
                b -= '0';
            *dst++ = 16*a+b;
            src+=3;
        } else {
            *dst++ = *src++;
        }
    }
    *dst++ = '\0';
}

int main(int argc, char *argv[]) {
    // Check if a command-line argument is provided
    if (argc < 2) {
        printf("Usage: %s <url>\n", argv[0]);
        return 1;
    }

    char decodedUrl[256];
    
    // Decode the URL-encoded string
    urldecode(decodedUrl, argv[1]);

    // Print the decoded URL
    printf("Decoded URL: %s\n", decodedUrl);

    return 0;
}

