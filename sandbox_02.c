#include <stdio.h>

// if you have a pointer to a type, adding one to the pointer moves to the next
// item of that type directly after it in memory.

int main() {

    int a[10] = {1, 2, 3, 4, 5};
    // int *p = a;" works just as well
    int *p = &a[0]; // Then let’s get a pointer to the first element in that
                    // array:

    printf("%d\n", *p); // Prints 1

    return 0;
}
