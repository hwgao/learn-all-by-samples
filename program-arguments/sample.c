#include <stdio.h>

int main(int argc, char **argv) {
    // argc is the number of arguments plus one
    // As program name is included
    printf("Arguments number with program name is %d\n", argc);
    for (int i = 0; i < argc; ++i) {
        // argv[0] is the program name
        // others are arguments
        printf("argv[%d] is %s\n", i, argv[i]);
    }

    return 0;
}
